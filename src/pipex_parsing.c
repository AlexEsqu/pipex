/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:36:04 by mkling            #+#    #+#             */
/*   Updated: 2024/09/10 22:26:43 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*extract_path_variable(char **envp)
{
	char	*paths;

	paths = NULL;
	while (*envp++)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			paths = ft_substr(*envp, 5, ft_strlen(*envp));
			if (!paths)
				return (perror("Failed to allocate for extracted path"), NULL);
			return (paths);
		}
	}
	return (NULL);
}

static char	*return_accessible_path(char **envp, char *cmd)
{
	char	*path_variable;
	char	**possible_paths;
	char	*tested_path;
	size_t	i;

	i = 0;
	path_variable = extract_path_variable(envp);
	if (path_variable == NULL)
		return (perror("No PATH variable found"), NULL);
	possible_paths = ft_split(path_variable, ':');
	free(path_variable);
	while (possible_paths[i])
	{
		tested_path = ft_strjoin(possible_paths[i++], cmd);
		if (!tested_path)
			return (perror("Failed to allocate for tested command path"), NULL);
		if (access(tested_path, F_OK | R_OK) == 0)
		{
			ft_free_tab(possible_paths);
			return (tested_path);
		}
		free(tested_path);
	}
	ft_free_tab(possible_paths);
	return (perror("No viable path found to this command"), NULL);
}

char	**get_cmd_argv(char *cmd_string)
{
	char	**cmd_argv;

	if (cmd_string == NULL || cmd_string[0] == '\0')
		return (perror("Empty Command"), NULL);
	cmd_argv = ft_split(cmd_string, ' ');
	if (!cmd_argv[0])
		return (perror("Failed to allocate the command string"), NULL);
	return (cmd_argv);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		return (perror("Failed to allocate the command string"), NULL);
	if (access(cmd, F_OK | R_OK) == 0)
		return (cmd);
	cmd_path = return_accessible_path(envp, cmd);
	return (cmd_path);
}

int	open_file(char *filepath, int mode)
{
	int	file_fd;

	file_fd = 0;
	if (mode == READ)
		file_fd = open(filepath, O_RDONLY);
	if (mode == WRITE)
		file_fd = open(filepath, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (mode == APPEND)
		file_fd = open(filepath, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (file_fd == -1)
		return (perror("Error while opening file"), 1);
	return (file_fd);
}
