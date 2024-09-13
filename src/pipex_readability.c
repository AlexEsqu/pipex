/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_readability.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:57:59 by mkling            #+#    #+#             */
/*   Updated: 2024/09/13 19:46:19 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_fork(pid_t *fork_pid)
{
	*fork_pid = fork();
	if (*fork_pid == -1)
		return (perror("Error while forking"), FORK_ERROR);
	return (OK);
}

int	create_pipe(int *pipe_fd, t_index *index)
{
	if (is_last_cmd(index))
		return (OK);
	if (pipe(pipe_fd) == -1)
		return (perror("Error while creating pipe"), PIPE_ERROR);
	return (OK);
}

int	close_pipe(int *pipe_fd, t_index *index)
{
	if (is_last_cmd(index))
		return (OK);
	close(pipe_fd[WRITE]);
	if (dup2(pipe_fd[READ], STDIN_FILENO) == -1)
		return (perror("Error while redirecting pipe to stdin"), DUP_ERROR);
	close(pipe_fd[READ]);
	return (OK);
}

int	assemble_heredoc(char *limiter)
{
	int		heredoc_fd;
	char	*result;

	heredoc_fd = open_file(HEREDOC_FILEPATH, WRITE);
	if (heredoc_fd == -1)
		return (perror("Unable to create temp heredoc"), -1);
	while (1)
	{
		write(STDIN_FILENO, "heredoc> ", 9);
		result = get_next_line(STDIN_FILENO);
		if (ft_strncmp(limiter, result, ft_strlen(limiter)) == 0)
			break ;
		write(heredoc_fd, result, ft_strlen(result));
	}
	close(heredoc_fd);
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
