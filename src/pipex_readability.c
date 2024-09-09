/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_readability.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:57:59 by mkling            #+#    #+#             */
/*   Updated: 2024/09/09 12:20:11 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_last_command(int *pipe_fd)
{
	return (pipe_fd == NULL);
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

int	open_file(char *filepath, int mode)
{
	int	file_fd;

	file_fd = 0;
	fprintf(stderr, "file to open = %s\n", filepath);
	if (mode == READ)
		file_fd = open(filepath, O_RDONLY);
	if (mode == WRITE)
		file_fd = open(filepath, O_WRONLY | O_TRUNC | O_CREAT);
	if (mode == APPEND)
		file_fd = open(filepath, O_WRONLY | O_APPEND | O_CREAT);
	if (file_fd == -1)
		return (perror("Error while opening file"), -1);
	return (file_fd);
}

int	create_pipe_and_fork(int *pipe_fd, pid_t *fork_pid)
{
	if (pipe(pipe_fd) == -1)
		return (perror("Error while creating pipe"), -1);
	*fork_pid = fork();
	if (*fork_pid == -1)
		return (perror("Error while forking"), -1);
	return (0);
}

int	close_and_wait_for_fork(int *pipe_fd, int fork_pid)
{
	close(pipe_fd[WRITE]);
	if (dup2(pipe_fd[READ], STDIN_FILENO) == -1)
		return (perror("Error while redirecting pipe to stdin"), -1);
	waitpid(fork_pid, NULL, 0);
	return (0);
}
