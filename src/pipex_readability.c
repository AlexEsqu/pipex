/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_readability.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:57:59 by mkling            #+#    #+#             */
/*   Updated: 2024/09/11 11:41:33 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_last_cmd(char **argv, int cmd_index)
{
	return (argv[cmd_index + 2] == NULL);
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
