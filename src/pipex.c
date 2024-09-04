/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:59:07 by mkling            #+#    #+#             */
/*   Updated: 2024/09/04 17:36:36 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *filepath, int mode)
{
	int	file_fd;

	file_fd = 0;
	if (mode == READ)
		file_fd = open(filepath, O_RDWR);
	else
		file_fd = open(filepath, O_WRONLY | O_TRUNC | O_CREAT);
	if (file_fd == -1)
		return (perror("Error while opening file"), -1);
	return (file_fd);
}

int	exec_cmd(int pipe_fd[], char **argv,
	char **envp, int cmd_index)
{
	char	**cmd_argv;
	char	*cmd_path;

	cmd_argv = get_cmd_argv(argv[cmd_index]);
	cmd_path = get_cmd_path(cmd_argv[0], envp);
	if (is_first_command(cmd_index))
	{
		if (redirect(open_file(argv[INFILE], READ), STDIN_FILENO) == -1
			|| redirect(pipe_fd[WRITE], STDOUT_FILENO) == -1)
			return (-1);
		close(pipe_fd[READ]);
		if (cmd_argv == NULL || cmd_path == NULL)
			exit(1);
	}
	if (is_last_command(cmd_index, 5))
	{
		if (redirect(open_file(argv[cmd_index + 1], WRITE),
				STDOUT_FILENO) == -1)
			return (-1);
	}
	execve(cmd_path, cmd_argv, envp);
	return (perror("Error while executing command"), 127);
}

int	main(int argc, char **argv, char *envp[])
{
	int	pipe_fd[2];
	int	fork_pid;

	if (argc != 5)
		return (perror("Invalid number of arguments"), 1);
	if (pipe(pipe_fd) == -1)
		return (perror("Error while creating pipe"), -1);
	fork_pid = fork();
	if (fork_pid == -1)
		return (perror("Error while forking"), -1);
	if (fork_pid == 0)
		exec_cmd(pipe_fd, argv, envp, CMD_1);
	close(pipe_fd[WRITE]);
	if (dup2(pipe_fd[READ], STDIN_FILENO) == -1)
		return (perror("Error while redirecting pipe to stdin"), -1);
	exec_cmd(NULL, argv, envp, CMD_2);
}
