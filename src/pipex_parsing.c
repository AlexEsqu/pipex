/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:36:04 by mkling            #+#    #+#             */
/*   Updated: 2024/08/18 17:02:12 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_array(char **array)
{
    int i = 0;

    if (array == NULL)
        return;

    while (array[i] != NULL)
    {
        free(array[i]);
        i++;
    }
    free(array);
}


int	find_viable_path(t_command *cmd, char *paths)
{
	char	*tested_path;
	char	**possible_paths;
	int		i;

	possible_paths = ft_split(paths, ':');
	free(paths);
	i = 0;
	while (possible_paths[i] != NULL)
	{
		if (possible_paths[i] == NULL)
			break ;
		tested_path = ft_strjoin(possible_paths[i], cmd->cmd_stem);
		if (access(tested_path, F_OK | R_OK) == 0)
		{
			free_array(possible_paths);
			cmd->cmd_path = tested_path;
			return (0);
		}
		else
			free(tested_path);
		i++;
	}
	free_array(possible_paths);
	return (perror("No viable path found to this command"), 1);
}

int	find_cmd_path(char **envp, t_command *cmd)
{
	char	*paths;
	int		i;

	paths = NULL;
	i = 0;
	while (*envp++)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			paths = ft_substr(*envp, 5, ft_strlen(*envp));
			return (find_viable_path(cmd, paths));
		}
	}
	cmd->cmd_path = NULL;
	return (perror("No PATH variable found"), 1);
}

int	parse_cmd(char *cmd_line, char **envp, t_command *cmd)
{
	cmd->cmd_argv = ft_split(cmd_line, ' ');
	if (cmd->cmd_argv == NULL || cmd->cmd_argv[0] == NULL)
	{
		perror("Wrong Command syntax");
		return (1);
	}
	cmd->cmd_stem = ft_strjoin("/", cmd->cmd_argv[0]);
	return (find_cmd_path(envp, cmd));
}

