/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:38:08 by mkling            #+#    #+#             */
/*   Updated: 2024/09/11 10:42:51 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect(int newfd, int oldfd)
{
	if (newfd == -1 || oldfd == -1)
		return (-1);
	if (dup2(newfd, oldfd) == -1)
	{
		close(newfd);
		return (perror("Error while redirecting to file"), -1);
	}
	close(newfd);
	return (0);
}

int	create_fork(pid_t *fork_pid)
{
	*fork_pid = fork();
	if (*fork_pid == -1)
		return (perror("Error while forking"), -1);
	return (0);
}

int	create_pipe(int *pipe_fd, char **argv, int cmd_index)
{
	if (!is_last_cmd(argv, cmd_index) && pipe(pipe_fd) == -1)
		return (perror("Error while creating pipe"), -1);
	return (0);
}

int	close_pipe(int *pipe_fd, char **argv, int cmd_index)
{
	if (is_last_cmd(argv, cmd_index))
		return (0);
	close(pipe_fd[WRITE]);
	if (dup2(pipe_fd[READ], STDIN_FILENO) == -1)
		return (perror("Error while redirecting pipe to stdin"), -1);
	close(pipe_fd[READ]);
	return (0);
}
