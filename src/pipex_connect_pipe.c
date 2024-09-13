/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_connect_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:54:35 by mkling            #+#    #+#             */
/*   Updated: 2024/09/13 19:53:21 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect(int newfd, int oldfd)
{
	if (newfd == -1 || oldfd == -1)
		return (INVALID_FD);
	if (dup2(newfd, oldfd) == -1)
	{
		close(newfd);
		return (DUP_ERROR);
	}
	close(newfd);
	return (OK);
}

int	open_file(char *filepath, int mode)
{
	int	file_fd;

	file_fd = 0;
	// fprintf(stderr, "file to open = %s\n", filepath);
	if (mode == READ)
		file_fd = open(filepath, O_RDONLY);
	if (mode == WRITE)
		file_fd = open(filepath, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (mode == APPEND)
		file_fd = open(filepath, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (file_fd == -1)
		return (OPEN_ERROR);
	return (file_fd);
}

int	re_stdin_by_infile_stdout_by_pipe(t_index *index, int *pipe_fd)
{
	int	infile_fd;

	if (index->heredoc_flag == 1)
		assemble_heredoc(index->argv[HEREDOC_LIMITER]);
	if (access(index->infile, F_OK) == -1)
		return (perror("No input file"), NO_FILE);
	if (access(index->infile, R_OK) == -1)
		return (perror("Forbidden input file"), READ_ERROR);
	infile_fd = open_file(index->infile, READ);
	if (infile_fd == -1)
		return (perror("Error while opening input file"), OPEN_ERROR);
	if (redirect(infile_fd, STDIN_FILENO) != OK)
		return (perror("Error while redirecting stdin to infile"), DUP_ERROR);
	return (replace_stdout_by_pipe_write(pipe_fd));
}

int	replace_stdout_by_outfile(char *outfilepath)
{
	int	outfile_fd;

	outfile_fd = open_file(outfilepath, WRITE);
	if (outfile_fd == -1)
		return (perror("Error while opening output file"), OPEN_ERROR);
	if (redirect(outfile_fd, STDOUT_FILENO) != OK)
		return (perror("Error while redirecting stdout to outfile"), DUP_ERROR);
	return (OK);
}

int	replace_stdout_by_pipe_write(int pipe_fd[])
{
	if (redirect(pipe_fd[WRITE], STDOUT_FILENO) == -1)
		return (perror("Error while redirecting stdout to pipe"), DUP_ERROR);
	close(pipe_fd[READ]);
	return (OK);
}
