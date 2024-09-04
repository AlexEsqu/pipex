/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_readability.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:57:59 by mkling            #+#    #+#             */
/*   Updated: 2024/09/04 17:08:02 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_even(int num)
{
	return (num % 2 == 0);
}

int	is_last_command(int cmd_index, int argc)
{
	return (cmd_index == argc - 2);
}

int	is_first_command(int cmd_index)
{
	return (cmd_index == CMD_1);
}

int	redirect(int newfd, int oldfd)
{
	if (newfd == -1 || oldfd == -1)
		return (-1);
	if (dup2(newfd, oldfd) == -1)
		return (perror("Error while redirecting to file"), -1);
	close(newfd);
	return (0);
}
