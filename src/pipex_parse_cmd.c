/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:36:04 by mkling            #+#    #+#             */
/*   Updated: 2024/09/13 18:38:37 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_accessible_path(t_index *index, t_cmd *cmd)
{
	char	*tested_path;
	size_t	i;

	i = 0;
	while (index->extracted_paths[i])
	{
		tested_path = ft_strjoin(index->extracted_paths[i++], cmd->cmd_path);
		if (!tested_path)
			free_cmd_then_exit(cmd, "Failed to allocate", MALLOC_FAIL, index);
		if (access(tested_path, F_OK | R_OK) == 0)
		{
			ft_free_tab(index->extracted_paths);
			cmd->cmd_path = tested_path;
			return (OK);
		}
		free(tested_path);
	}
	ft_free_tab(index->extracted_paths);
	return (free_cmd_then_exit(cmd, "No path found", CANT_FIND_CMD, index));
}

int	get_cmd_argv(t_cmd *cmd, t_index *index)
{
	cmd->cmd_argv = NULL;
	if (index->argv[cmd->cmd_index] == NULL)
		free_cmd_then_exit(cmd, "Empty Command", CANT_FIND_CMD, index);
	cmd->cmd_argv = ft_split(index->argv[cmd->cmd_index], ' ');
	if (!cmd->cmd_argv)
		free_cmd_then_exit(cmd, "Failed to allocate", MALLOC_FAIL, index);
	return (OK);
}

int	get_cmd_path(t_cmd *cmd, t_index *index)
{
	cmd->cmd_path = ft_strjoin("/", cmd->cmd_argv[0]);
	if (!cmd->cmd_path)
		free_cmd_then_exit(cmd, "Failed to allocate", MALLOC_FAIL, index);
	if (access(cmd->cmd_path, F_OK) == 0)
		return (check_cmd(cmd, index));
	if (index->extracted_paths == NULL)
		free_cmd_then_exit(cmd, "No PATH variable found", CANT_FIND_CMD, index);
	if (find_accessible_path(index, cmd) != OK)
		free_cmd_then_exit(cmd, NULL, 0, index);
	return (check_cmd(cmd, index));
}

int	free_cmd_then_exit(t_cmd *cmd, char *errnote, int errnum, t_index *index)
{
	int	exit_code;

	exit_code = GENERAL_ERROR;
	if (errnote)
		perror(errnote);
	if (cmd != NULL)
	{
		if (cmd->cmd_exit_code != 0)
			exit_code = cmd->cmd_exit_code;
		if (cmd->cmd_argv)
			ft_free_tab(cmd->cmd_argv);
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		free(cmd);
	}
	if (errnum != OK)
		exit_code = errnum;
	index->exit_code = exit_code;
	exit(exit_code);
}

t_cmd	*get_cmd(t_index *index)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_exit_code = 0;
	cmd->cmd_index = index->current_cmd;
	if (get_cmd_argv(cmd, index) != OK)
		return (NULL);
	if (get_cmd_path(cmd, index) != OK)
		return (NULL);
	return (cmd);
}
