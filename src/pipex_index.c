/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:38:08 by mkling            #+#    #+#             */
/*   Updated: 2024/09/13 19:10:38 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_cmd(t_cmd *cmd, t_index *index)
{
	if (cmd->cmd_exit_code != OK)
		return (cmd->cmd_exit_code);
	if (cmd->cmd_path == NULL)
		free_cmd_then_exit(cmd, NULL, CANT_EXECUTE_CMD, index);
	if (is_directory(cmd->cmd_path))
		free_cmd_then_exit(cmd, "Cmd is a directory", CANT_EXECUTE_CMD, index);
	if (access(cmd->cmd_path, X_OK) != OK)
		free_cmd_then_exit(cmd, "Cannot execute cmd", CANT_EXECUTE_CMD, index);
	return (OK);
}

int	is_directory(char *cmd)
{
	int	fd;

	fd = open(cmd, __O_DIRECTORY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	extract_if_path_variable(t_index *index)
{
	char	*paths;

	paths = NULL;
	while (*index->envp++)
	{
		if (ft_strncmp(*index->envp, "PATH=", 5) == 0)
		{
			paths = ft_substr(*index->envp, 5, ft_strlen(*index->envp));
			if (!paths)
				return (perror("Failed to allocate for path"), MALLOC_FAIL);
			index->extracted_paths = ft_split(paths, ':');
			if (!index->extracted_paths)
				return (perror("Failed to split path variable"), MALLOC_FAIL);
			free(paths);
			return (OK);
		}
	}
	index->extracted_paths = NULL;
	return (OK);
}

int	free_index(t_index *index)
{
	int	exit_code;

	exit_code = GENERAL_ERROR;
	if (!index)
		return (MALLOC_FAIL);
	ft_free_tab(index->extracted_paths);
	if (index->exit_code != OK)
		exit_code = index->exit_code;
	free(index);
	return (exit_code);
}

t_index	*create_index(int argc, char **argv, char **envp)
{
	t_index	*index;

	index = malloc(sizeof(t_index));
	if (!index)
		exit(MALLOC_FAIL);
	index->heredoc_flag = (ft_strcmp(argv[INFILE], "HERE_DOC") == 0);
	index->argc = argc;
	index->argv = argv;
	index->envp = envp;
	if (extract_if_path_variable(index) != OK)
		exit(MALLOC_FAIL);
	if (index->heredoc_flag)
		index->infile = HEREDOC_FILEPATH;
	else
		index->infile = argv[INFILE];
	index->outfile = argv[argc - 1];
	index->last_cmd = argc - 2;
	index->current_cmd = CMD_1 + index->heredoc_flag;
	index->exit_code = 0;
	return (index);
}

