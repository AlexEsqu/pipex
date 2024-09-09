/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:59:07 by mkling            #+#    #+#             */
/*   Updated: 2024/09/09 13:14:32 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	connect_pipe(int pipe_fd[], char **argv,
	int cmd_index)
{
	if (cmd_index == CMD_1)
	{
		if (redirect(open_file(argv[INFILE], READ), STDIN_FILENO) == -1
			|| redirect(pipe_fd[WRITE], STDOUT_FILENO) == -1)
			return (-1);
		close(pipe_fd[READ]);
	}
	else if (is_last_command(pipe_fd))
	{
		if (redirect(open_file(argv[cmd_index + 1], WRITE),
				STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (redirect(pipe_fd[WRITE], STDOUT_FILENO) == -1)
			return (-1);
		close(pipe_fd[READ]);
	}
	return (0);
}

int	exec_cmd(int pipe_fd[], char **argv,
	char **envp, int cmd_index)
{
	char	**cmd_argv;
	char	*cmd_path;

	if (connect_pipe(pipe_fd, argv, cmd_index) == -1)
		return (-1);
	cmd_argv = get_cmd_argv(argv[cmd_index]);
	cmd_path = get_cmd_path(cmd_argv[0], envp);
	if (!is_last_command(pipe_fd) && cmd_path == NULL)
		exit(1);
	execve(cmd_path, cmd_argv, envp);
	return (perror("Error while executing command"), 127);
}

int	main(int argc, char **argv, char *envp[])
{
	int	pipe_fd[2];
	int	fork_pid;
	int	cmd_index;

	if (argc < 5)
		return (perror("Invalid number of arguments"), -1);
	if (strcmp(argv[INFILE], "HERE_DOC") == 0)
		return (adjust_for_heredoc(argc, argv, envp));
	cmd_index = CMD_1;
	while (cmd_index < argc - 2)
	{
		if (create_pipe_and_fork(pipe_fd, &fork_pid) == -1)
			return (-1);
		if (fork_pid == 0)
			exec_cmd(pipe_fd, argv, envp, cmd_index);
		if (close_and_wait_for_fork(pipe_fd, fork_pid) == -1)
			return (-1);
		cmd_index++;
	}
	exec_cmd(NULL, argv, envp, cmd_index);
}
