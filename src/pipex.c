/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:59:07 by mkling            #+#    #+#             */
/*   Updated: 2024/09/10 23:07:50 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TESTING FUNCTION :
// void	check_open_fds(void)
// {
// 	int	fd;

// 	fd = 0;
// 	while (fd < 1024)
// 	{
// 		if (fcntl(fd, F_GETFD) != -1)
// 			fprintf(stderr, "File descriptor %d is open\n", fd++);
// 		else
// 			fd++;
// 	}
// }
//
// ALTERNATIVE:
// hang program (add while(1) or sleep(10000))
// preferably in heredoc side function,
// to have a fork executing last function
// obtain pid running "./pipex &" in shell
// check proc/<pid>/fd directory
// obtain open fd running "ls -lrt" in shell

static int	connect_pipe(int pipe_fd[], char **argv, int cmd_index)
{
	int	filefd[2];

	if (is_last_cmd(argv, cmd_index))
	{
		filefd[WRITE] = open_file(argv[cmd_index + 1], WRITE);
		if (filefd[WRITE] == -1 || redirect(filefd[WRITE], STDOUT_FILENO) == -1)
			return (CANT_OPEN_FILE);
		return (0);
	}
	if (cmd_index == CMD_1)
	{
		filefd[READ] = open_file(argv[INFILE], READ);
		if (filefd[READ] == -1 || redirect(filefd[READ], STDIN_FILENO) == -1)
			return (CANT_OPEN_FILE);
	}
	if ((pipe_fd[WRITE] == -1 && cmd_index == CMD_1)
		|| redirect(pipe_fd[WRITE], STDOUT_FILENO) == -1)
		return (CANT_OPEN_FILE);
	close(pipe_fd[READ]);
	return (0);
}

static int	exec_cmd(int pipe_fd[], char **argv, char **envp, int cmd_index)
{
	char	**cmd_argv;
	char	*cmd_path;

	if (connect_pipe(pipe_fd, argv, cmd_index) != OK)
		exit(-1);
	cmd_argv = get_cmd_argv(argv[cmd_index]);
	cmd_path = get_cmd_path(cmd_argv[0], envp);
	if (cmd_path == NULL)
		exit(CANT_FIND_CMD);
	return (execve(cmd_path, cmd_argv, envp));
}

static int	wait_on_all_forks(int fork_pid)
{
	int	exit_code;

	exit_code = 0;
	waitpid(fork_pid, &exit_code, 0);
	exit_code = WEXITSTATUS(exit_code);
	waitpid(-1, NULL, 0);
	return (exit_code);
}

int	main(int argc, char **argv, char *envp[])
{
	int	pipe_fd[2];
	int	fork_pid;
	int	cmd_index;

	if (argc < 5)
		return (perror("Invalid number of arguments"), -1);
	if (ft_strcmp(argv[INFILE], "HERE_DOC") == 0)
		return (adjust_for_heredoc(argc, argv, envp));
	cmd_index = CMD_1;
	while (cmd_index < argc - 1)
	{
		if ((create_pipe(pipe_fd, argv, cmd_index) != OK)
			|| create_fork(&fork_pid) != OK)
			return (GENERAL_ERROR);
		if (fork_pid == IS_FORK)
			exec_cmd(pipe_fd, argv, envp, cmd_index);
		if (close_pipe(pipe_fd, argv, cmd_index) != OK)
			return (GENERAL_ERROR);
		cmd_index++;
	}
	return (wait_on_all_forks(fork_pid));
}
