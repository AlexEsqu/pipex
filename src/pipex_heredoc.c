/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:52:36 by mkling            #+#    #+#             */
/*   Updated: 2024/09/09 14:22:30 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc_cleanup(int *heredoc_fd)
{
	// if (heredoc_fd != NULL)
	// 	close(*heredoc_fd);
	fprintf(stderr, "heredoc fd = %p\n", heredoc_fd);
	// if (access("tmp/.heredoc", F_OK))
	// 	unlink("tmp/.heredoc");
}

int	read_stdin_into_heredoc(char *limiter, int *heredoc_fd)
{
	char	*result;

	write(STDIN_FILENO, "heredoc> ", 9);
	result = get_next_line(STDIN_FILENO);
	fprintf(stderr, "result = %s\n", result);
	if (strncmp(limiter, result, ft_strlen(limiter)) == 0)
		return (0);
	write(*heredoc_fd, result, ft_strlen(result));
	return (1);
}

int	assemble_heredoc(char *limiter, char *heredoc_filepath, int *heredoc_fd)
{
	*heredoc_fd = open_file(heredoc_filepath, APPEND);
	if (*heredoc_fd == -1)
		return (perror("Unable to create temp heredoc"), -1);
	fprintf(stderr, "in heredoc\n");
	fprintf(stderr, "limiter = %s\n", limiter);
	while (read_stdin_into_heredoc(limiter, heredoc_fd))
		;
	fprintf(stderr, "leaving heredoc\n");
	return (0);
}

char	**update_arguments(int argc, char **argv, char *heredoc_filepath)
{
	char	**updated_argv;
	int		index;

	argc = argc - 1;
	updated_argv = malloc(argc * sizeof(char *));
	if (!updated_argv)
		return (perror("Failed to allocate for heredoc path"), NULL);
	updated_argv[PROGRAM_NAME] = ft_strdup(argv[PROGRAM_NAME]);
	updated_argv[INFILE] = ft_strdup(heredoc_filepath);
	index = CMD_1;
	while (index < argc)
	{
		updated_argv[index] = strdup(argv[index + 1]);
		fprintf(stderr, "argv index = %s\n", updated_argv[index]);
		if (!argv[index] || !argv[INFILE] || !argv[PROGRAM_NAME])
		{
			free_array(argv);
			free_array(updated_argv);
			return (NULL);
		}
		index++;
		fprintf(stderr, "index = %d\n", index);
	}
	fprintf(stderr, "out of update args\n");
	updated_argv[index] = NULL;
	fprintf(stderr, "infile = %s\n", updated_argv[INFILE]);
	return (updated_argv);
}

int	adjust_for_heredoc(int argc, char **argv, char **envp)
{
	char	*heredoc_filepath;
	int		heredoc_fd;
	char	**updated_argv;

	heredoc_cleanup(NULL);
	heredoc_filepath = "tmp/.heredoc";
	assemble_heredoc(argv[H_LIMITER], heredoc_filepath, &heredoc_fd);
	updated_argv = update_arguments(argc, argv, heredoc_filepath);
	if (!heredoc_filepath)
		return (-1);
	main(argc - 1, updated_argv, envp);
	heredoc_cleanup(&heredoc_fd);
	return (0);
}


