/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_readability.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:57:59 by mkling            #+#    #+#             */
/*   Updated: 2024/09/16 10:04:20 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_fork(pid_t *fork_pid, t_index *index)
{
	*fork_pid = fork();
	if (*fork_pid == -1)
	{
		perror("Error while forking");
		free_index(index);
		exit(FORK_ERROR);
	}
	return (OK);
}

int	create_pipe(int *pipe_fd, t_index *index)
{
	if (is_last_cmd(index))
		return (OK);
	if (pipe(pipe_fd) == -1)
	{
		perror("Error while creating pipe");
		free_index(index);
		exit(PIPE_ERROR);
	}
	return (OK);
}

int	close_pipe(int *pipe_fd, t_index *index)
{
	if (is_last_cmd(index))
		return (OK);
	close(pipe_fd[WRITE]);
	if (dup2(pipe_fd[READ], STDIN_FILENO) == -1)
	{
		perror("Error while redirecting pipe to stdin");
		free(index);
		exit(DUP_ERROR);
	}
	close(pipe_fd[READ]);
	return (OK);
}

int	is_last_cmd(t_index *index)
{
	return (index->current_cmd == index->last_cmd);
}

int	is_first_cmd(t_index *index)
{
	return (index->current_cmd == CMD_1 + index->heredoc_flag);
}
