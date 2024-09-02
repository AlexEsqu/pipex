/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:59:07 by mkling            #+#    #+#             */
/*   Updated: 2024/09/02 15:28:46 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *filepath, int mode)
{
	int	file_fd;

	if (mode == READ)
		file_fd = open(file_fd, O_RDWR);
	else
		file_fd = open(file_fd, O_WRONLY | O_TRUNC | O_CREAT);
	if (file_fd == -1)
		return (perror("Error while opening file"), -1);
	return (file_fd);
}

int	redirect(int newfd, int oldfd)
{
	if (dup2(newfd, oldfd) == -1)
		return (perror("Error while redirecting to file"), -1);
	close(newfd);
	return (0);
}

int	execute_cmd_tru_pipe(int pipe_fd[], char **argv, char **envp, int index)
{
	char	**cmd_argv;
	char	*cmd_path;

	close(pipe_fd[READ]);
	cmd_argv = get_cmd_argv(argv[index]);
	cmd_path = get_cmd_path(cmd_argv[0], envp);
	if (redirect(pipe_fd[WRITE], STDOUT_FILENO) == -1 || cmd_path == NULL)
		exit(-1);
	execve(cmd_path, cmd_argv, envp);
	return (perror("Error while executing command"), 127);
}

// int	exec_first_cmd_from_infile_to_pipe(int pipe_fd[], char **argv,
// 	char **envp, int cmd_index)
// {
// 	char	**cmd_argv;
// 	char	*cmd_path;

// 	close(pipe_fd[READ]);
// 	if (dup2(pipe_fd[WRITE], STDOUT_FILENO) == -1)
// 		return (perror("Error while redirecting pipe write to stdout"), -1);
// 	close(pipe_fd[WRITE]);
// 	cmd_argv = get_cmd_argv(argv[cmd_index]);
// 	cmd_path = get_cmd_path(cmd_argv[0], envp);
// 	if (cmd_argv == NULL || cmd_path == NULL)
// 		exit(1);
// 	execve(cmd_path, cmd_argv, envp);
// 	return (perror("Error while executing reading command"), 127);
// }

// int	exec_middle_cmd_from_pipe_to_pipe(int pipe_fd[], char **argv,
// 	char **envp, int cmd_index)
// {
// 	char	**cmd_argv;
// 	char	*cmd_path;

// 	close(pipe_fd[WRITE]);
// 	cmd_argv = get_cmd_argv(argv[cmd_index]);
// 	cmd_path = get_cmd_path(cmd_argv[0], envp);
// 	execve(cmd_path, cmd_argv, envp);
// 	return (perror("Error while executing reading command"), 127);
// }

// int	exec_last_cmd_from_pipe_to_outfile(int pipe_fd[], char **argv,
// 	char **envp, int cmd_index)
// {
// 	int		outfile_fd;
// 	char	**cmd_argv;
// 	char	*cmd_path;

// 	redirect_to_filepath(argv[argc])
// 	close(pipe_fd[WRITE]);
// 	if (dup2(pipe_fd[READ], STDIN_FILENO) == -1)
// 		return (perror("Error while redirecting pipe read to stdin"), 1);
// 	close(pipe_fd[READ]);
// 	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
// 		return (perror("Error while redirecting stdout to outfile"), 1);
// 	close(outfile_fd);
// 	cmd_argv = get_cmd_argv(argv[cmd_index]);
// 	cmd_path = get_cmd_path(cmd_argv[0], envp);
// 	execve(cmd_path, cmd_argv, envp);
// 	return (perror("Error while executing reading command"), 127);
// }

int	lay_pipe(char **argv, char **envp, int cmd_index)
{
	int	pipe_fd[2];
	int	fork_pid;
	int	exit_status;

	if (pipe(pipe_fd) == -1)
		return (perror("Error while creating pipe"), -1);
	fork_pid = fork();
	if (fork_pid == -1)
		return (perror("Error while forking"), -1);
	if (fork_pid == 0)
		exec_cmd_thru_pipe(pipe_fd, argv, envp, cmd_index);
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	waitpid(fork_pid, &exit_status, 0);
	return (0);
}

// int	set_files_as_stdin_n_out(char *infile_path, char *outfile_path)
// {
// 	int	infile_fd;
// 	int	outfile_fd;

// 	infile_fd = open(infile_path, O_RDWR);
// 	if (infile_fd == -1)
// 		perror("Error while opening infile");
// 	outfile_fd = open(outfile_path, O_WRONLY | O_TRUNC | O_CREAT);
// 	if (outfile_fd == -1)
// 		return (perror("Error while opening outfile"), 1);
// 	if (dup2(infile_fd, STDIN_FILENO) == -1)
// 		return (perror("Error while redirecting infile to stdin"), 1);
// 	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
// 		return (perror("Error while redirecting stdout to outfile"), 1);
// 	close(infile_fd);
// 	close(outfile_fd);
// 	return (0);
// }

int	main(int argc, char **argv, char *envp[])
{
	int	cmd_index;
	int	infile_fd;
	int	exit_status;

	exit_status = 0;
	cmd_index = CMD_1;
	while (argc >= 5)
	{
		infile_fd = open_file(argv[INFILE], READ);
		if (infile_fd == -1 || redirect_to_file(infile_fd, STDIN_FILENO) == -1)
			return (-1);
		while (cmd_index < argc - 1)
		{
			if (lay_pipe(argc, argv, envp, cmd_index) == -1)
				return (-1);
			cmd_index++;
		}
		return (exit_status);
	}
	return (perror("Invalid number of arguments"), 1);
}
