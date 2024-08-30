/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:59:07 by mkling            #+#    #+#             */
/*   Updated: 2024/08/28 17:50:38 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_cmd_tru_pipe(int pipe_fd[], char **argv, char **envp, int index)
{
	char	**cmd_argv;
	char	*cmd_path;

	//fprintf(stderr, "is in fork\n");
	write(0, "1 fork is stdin\n", 16);
	write(1, "1 fork is stdout\n", 17);
	if (dup2(pipe_fd[WRITE], STDOUT_FILENO) == -1)
		return (perror("Error while redirecting pipe write to stdout"), -1);
	close(pipe_fd[WRITE]);
	close(pipe_fd[READ]);
	cmd_argv = get_cmd_argv(argv[index]);
	//fprintf(stderr, "cmd argv is %s\n", cmd_argv[0]);
	cmd_path = get_cmd_path(cmd_argv[0], envp);
	//fprintf(stderr, "cmd path is %s\n", cmd_path);
	write(0, "2 fork is stdin\n", 16);
	write(1, "2 fork is stdout\n", 17);
	if (cmd_argv[0] == 0 || cmd_path == NULL)
		exit(1);
	execve(cmd_path, cmd_argv, envp);
	return (perror("Error while executing command"), 127);
}

int	pipe_and_fork(char **argv, char **envp, int cmd_index, int *exit_status)
{
	int	pipe_fd[2];
	int	fork_pid;

	write(0, "1 parent is stdin\n", 18);
	write(1, "1 parent is stdout\n", 19);
	if (pipe(pipe_fd) == -1)
		return (perror("Error while creating pipe"), -1);
	fork_pid = fork();
	if (fork_pid == -1)
		return (perror("Error while forking"), -1);
	if (fork_pid == 0)
		execute_cmd_tru_pipe(pipe_fd, argv, envp, cmd_index);
	//fprintf(stderr, "is parent\n");
	close(pipe_fd[WRITE]);
	if (dup2(pipe_fd[READ], STDIN_FILENO) == -1)
		return (perror("Error while redirecting pipe read to stdin"), -1);
	write(0, "2 parent is stdin\n", 18);
	write(1, "2 parent is stdout\n", 19);
	waitpid(fork_pid, exit_status, 0);
	return (0);
}

int	set_files_as_stdin_n_out(char *infile_path, char *outfile_path)
{
	int	infile_fd;
	int	outfile_fd;

	// infile_fd = open(infile_path, O_RDONLY);
	infile_fd = open(infile_path, O_RDWR);
	if (infile_fd == -1)
		perror("Error while opening infile");
	else if (dup2(infile_fd, STDIN_FILENO) == -1)
		return (perror("Error while redirecting infile to stdin"), 1);
	outfile_fd = open(outfile_path, O_WRONLY | O_TRUNC | O_CREAT);
	if (outfile_fd == -1)
		return (perror("Error while opening outfile"), -1);
	else if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		return (perror("Error while redirecting stdout to outfile"), 1);
	return (0);
}

int	main(int argc, char **argv, char *envp[])
{
	int	cmd_index;
	int	exit_status;

	exit_status = 0;
	if (argc >= 5)
	{
		if (set_files_as_stdin_n_out(argv[1], argv[argc - 1]) == -1)
			return (-1);
		write(0, "is stdin\n", 9);
		write(1, "is stdout\n", 10);
		cmd_index = CMD_1;
		while (cmd_index < argc - 1)
		{
			if (pipe_and_fork(argv, envp, cmd_index, &exit_status) == -1)
				return (-1);
			cmd_index++;
			//fprintf(stderr, "exit status = %d\n", exit_status);
		}
		return (exit_status);
	}
	return (perror("Invalid number of arguments"), 1);
}
