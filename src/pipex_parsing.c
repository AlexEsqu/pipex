/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:36:04 by mkling            #+#    #+#             */
/*   Updated: 2024/09/02 13:53:13 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}*/

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

	path_variable = extract_path_variable(envp);
	if (path_variable == NULL)
		return (perror("No PATH variable found"), NULL);
	possible_paths = ft_split(path_variable, ':');
	free(path_variable);
	while (*possible_paths != NULL)
	{
		tested_path = ft_strjoin(*possible_paths++, cmd);
		if (!tested_path)
			return (perror("Failed to allocate for tested command path"), NULL);
		if (access(tested_path, F_OK | R_OK) == 0)
		{
			//free_array(possible_paths); TROUBLE TO FREE ARRAY
			return (tested_path);
		}
		free(tested_path);
	}
	//free_array(possible_paths);
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
	// fprintf(stderr, "cmd stem is = %s\n", cmd);
	if (access(cmd, F_OK | R_OK) == 0)
		return (cmd);
	cmd_path = return_accessible_path(envp, cmd);
	return (cmd_path);
}
