/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mult_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:31:54 by mkling            #+#    #+#             */
/*   Updated: 2024/09/04 18:00:08 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/pipex.h"

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

int	connect_pipes(int *pipe_fd[2], int cmd_index)
{
	if (!is_first_command(cmd_index))
	{
		if (dup2(pipe_fd[PREVIOUS][READ], STDIN_FILENO) == -1)
			return (perror("Error while connecting pipes"), -1);
	}
	if (dup2(pipe_fd[CURRENT][WRITE], STDOUT_FILENO) == -1)
		return (perror("Error while connecting pipes"), -1);
	return (0);
}

void	swap_pipe(int **pipe_fd)
{
	int	*pipe_current;

	pipe_current = pipe_fd[CURRENT];
	pipe_fd[CURRENT] = pipe_fd[PREVIOUS];
	pipe_fd[PREVIOUS] = pipe_current;
}

void	close_unneeded_fd(int **pipe_fd, int cmd_index)
{
	if (is_first_command(cmd_index))
		close(pipe_fd[CURRENT][WRITE]);
	close(pipe_fd[PREVIOUS][READ]);
}

int	exec_cmd(int **pipe_fd, char **argv,
	char **envp, int cmd_index)
{
	char	**cmd_argv;
	char	*cmd_path;

	cmd_argv = get_cmd_argv(argv[cmd_index]);
	cmd_path = get_cmd_path(cmd_argv[0], envp);
	if (!pipe_fd)
	{
		if (redirect(open_file(argv[cmd_index + 1], WRITE),
				STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (connect_pipes(pipe_fd, cmd_index) == -1)
		return (-1);
	execve(cmd_path, cmd_argv, envp);
	return (perror("Error while executing command"), 127);
}

int	main(int argc, char **argv, char *envp[])
{
	int	pipe_fd[2][2];
	int	fork_pid;
	int	cmd_index;

	if (argc != 5)
		return (perror("Invalid number of arguments"), 1);
	cmd_index = CMD_1;
	while (cmd_index < argc - 2)
	{
		if (pipe(pipe_fd[CURRENT]) == -1)
			return (perror("Error while creating pipe"), -1);
		fork_pid = fork();
		if (fork_pid == -1)
			return (perror("Error while forking"), -1);
		if (fork_pid == 0)
			exec_cmd(pipe_fd, argv, envp, cmd_index);
		wait(NULL);
		close(pipe_fd[CURRENT][WRITE]);
		swap_pipe(pipe_fd);
		cmd_index++;
	}
	if (dup2(pipe_fd[PREVIOUS][READ], STDIN_FILENO) == -1)
		return (perror("Error while connecting pipes"), -1);
	exec_cmd(NULL, argv, envp, CMD_2);
}
