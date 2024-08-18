/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:59:07 by mkling            #+#    #+#             */
/*   Updated: 2024/08/18 16:15:14 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipe_out_child_process(char **argv, int pipe_fd[],
	t_command *cmd2, char **envp)
{
	int	outfile_fd;

	outfile_fd = open(argv[OUTFILE], O_WRONLY | O_TRUNC);
	if (outfile_fd == -1)
		return (perror("Error while opening infile"), 1);
	if (dup2(pipe_fd[READ], STDIN_FILENO) == -1)
		return (perror("Error while redirecting pipe read to stdin"), 1);
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		return (perror("Error while redirecting stdout to outfile"), 1);
	close(outfile_fd);
	execve(cmd2->cmd_path, cmd2->cmd_argv, envp);
	return (perror("Error while executing reading command"), 1);
}

int	pipe_in_child_process(char **argv, int pipe_fd[],
	t_command *cmd1, char **envp)
{
	int	infile_fd;

	infile_fd = open(argv[INFILE], O_RDONLY);
	if (infile_fd == -1)
		return (perror("Error while opening outfile"), 1);
	if (dup2(pipe_fd[WRITE], STDOUT_FILENO) == -1)
		return (perror("Error while redirecting pipe write to stdout"), 1);
	close(pipe_fd[WRITE]);
	close(pipe_fd[READ]);
	execve(cmd1->cmd_path, cmd1->cmd_argv, envp);
	return (perror("Error while executing writing command"), 1);
}

int	handle_pipe(char **argv, t_command *cmd1, t_command *cmd2, char **envp)
{
	int	pid_fork1;
	int	pid_fork2;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("Error while creating pipe"), 1);
	pid_fork1 = fork();
	if (pid_fork1 == 0)
		pipe_in_child_process(argv, pipe_fd, cmd1, envp);
	pid_fork2 = fork();
	if (pid_fork2 == 0)
		pipe_out_child_process(argv, pipe_fd, cmd2, envp);
	if (pid_fork1 == -1 || pid_fork2 == -1)
		return (perror("Error while forking"), 1);
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	waitpid(pid_fork1, NULL, 0);
	waitpid(pid_fork2, NULL, 0);
	return (0);
}

int	main(int argc, char **argv, char *envp[])
{
	t_command	cmd1;
	t_command	cmd2;

	if (argc == 5)
	{
		if (parse_cmd(argv[CMD_1], envp, &cmd1) == 1
			|| parse_cmd(argv[CMD_2], envp, &cmd2) == 1)
			return (1);
		return (handle_pipe(argv, &cmd1, &cmd2, envp));
	}
	return (perror("Invalid number of arguments"), 1);
}
