/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:59:07 by mkling            #+#    #+#             */
/*   Updated: 2024/09/09 17:39:28 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void check_open_fds(void)
{
    int fd;
    for (fd = 0; fd < 1024; fd++) // Check up to 1024 file descriptors
    {
        if (fcntl(fd, F_GETFD) != -1) // If fcntl returns -1, the fd is not open
        {
            printf("File descriptor %d is open\n", fd);
        }
    }
}

int	connect_pipe(int pipe_fd[], char **argv, int cmd_index)
{
	int	file_fd[2];

	if (cmd_index == CMD_1)
	{
		file_fd[READ] = open_file(argv[INFILE], READ);
		if (redirect(file_fd[READ], STDIN_FILENO) == -1
			|| redirect(pipe_fd[WRITE], STDOUT_FILENO) == -1)
			return (-1);
		close(pipe_fd[READ]);
	}
	else if (is_last_command(pipe_fd))
	{
		file_fd[WRITE] = open_file(argv[cmd_index + 1], WRITE);
		if (redirect(file_fd[WRITE], STDOUT_FILENO) == -1)
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

int	exec_cmd(int pipe_fd[], char **argv, char **envp, int cmd_index)
{
	char	**cmd_argv;
	char	*cmd_path;

	// fprintf(stderr, "to be exec = %s\n", argv[cmd_index]);
	if (connect_pipe(pipe_fd, argv, cmd_index) == -1)
		return (-1);
	cmd_argv = get_cmd_argv(argv[cmd_index]);
	cmd_path = get_cmd_path(cmd_argv[0], envp);
	if (!is_last_command(pipe_fd) && cmd_path == NULL)
		exit(1);
	return (execve(cmd_path, cmd_argv, envp));
}

int	main(int argc, char **argv, char *envp[])
{
	int	pipe_fd[4];
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
		if (fork_pid IS_FORK)
			exec_cmd(pipe_fd, argv, envp, cmd_index);
		if (close_and_wait_for_fork(pipe_fd, fork_pid) == -1)
			return (-1);
		cmd_index++;
	}
	check_open_fds();
	close(2);
	exec_cmd(NULL, argv, envp, cmd_index);
}
