/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:52:36 by mkling            #+#    #+#             */
/*   Updated: 2024/09/10 13:34:42 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	read_stdin_into_heredoc(char *limiter, int *heredoc_fd)
{
	char	*result;

	write(STDIN_FILENO, "heredoc> ", 9);
	result = get_next_line(STDIN_FILENO);
	if (strncmp(limiter, result, ft_strlen(limiter)) == 0)
		return (0);
	write(*heredoc_fd, result, ft_strlen(result));
	return (1);
}

int	assemble_heredoc(char *limiter, char *heredoc_filepath, int *heredoc_fd)
{
	*heredoc_fd = open_file(heredoc_filepath, WRITE);
	if (*heredoc_fd == -1)
		return (perror("Unable to create temp heredoc"), -1);
	while (read_stdin_into_heredoc(limiter, heredoc_fd))
		;
	close(*heredoc_fd);
	return (0);
}

char	**update_arguments(int argc, char **argv, char *heredoc_filepath)
{
	char	**updated_argv;
	int		index;

	updated_argv = malloc(argc * sizeof(char *));
	if (!updated_argv)
		return (perror("Failed to allocate for heredoc path"), NULL);
	updated_argv[PROGRAM_NAME] = ft_strdup(argv[PROGRAM_NAME]);
	updated_argv[INFILE] = ft_strdup(heredoc_filepath);
	index = CMD_1;
	while (index < argc - 1)
	{
		updated_argv[index] = ft_strdup(argv[index + 1]);
		if (!argv[index++] || !argv[INFILE] || !argv[PROGRAM_NAME])
			return (free_array(argv), free_array(updated_argv), NULL);
	}
	updated_argv[index] = NULL;
	return (updated_argv);
}

int	adjust_for_heredoc(int argc, char **argv, char **envp)
{
	int		heredoc_fd;
	char	*heredoc_filepath;
	char	**updated_argv;
	int		heredoc_fork_pid;

	heredoc_filepath = "tmp/.heredoc";
	assemble_heredoc(argv[H_LIMITER], heredoc_filepath, &heredoc_fd);
	updated_argv = update_arguments(argc, argv, heredoc_filepath);
	if (!heredoc_filepath)
		return (-1);
	heredoc_fork_pid = fork();
	if (heredoc_fork_pid == -1)
		return (perror("Error while forking"), -1);
	if (heredoc_fork_pid IS_FORK)
		main(argc - 1, updated_argv, envp);
	waitpid(heredoc_fork_pid, 0, 0);
	unlink("tmp/.heredoc");
	free_array(updated_argv);
	return (0);
}


