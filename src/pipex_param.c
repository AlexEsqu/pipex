/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:36:04 by mkling            #+#    #+#             */
/*   Updated: 2024/08/15 19:44:00 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_access_path(char *cmd, char **possible_paths)
{
	char	*viable_path;

	while (*possible_paths)
	{
		viable_path = ft_strjoin(*possible_paths, cmd);
		if (access(viable_path, F_OK | X_OK))
			return (viable_path);
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	cmd = ft_strjoin("/", ft_split(cmd, ' ')[0]);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	path = check_access_path(cmd, ft_split(path, ':'));
	fprintf(stderr, "cmd %s path = %s\n", cmd, path);
	return (path);
}


