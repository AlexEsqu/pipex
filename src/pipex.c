/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:59:07 by mkling            #+#    #+#             */
/*   Updated: 2024/08/17 13:18:35 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	writing_child_process(int file_descriptors[], t_command *cmd1, char **envp)
{
	dup2(file_descriptors[1], STDOUT_FILENO);
	close(file_descriptors[0]);
	close(file_descriptors[1]);
	execve(cmd1->cmd_path, cmd1->cmd_argv, envp);
	return (1);
}

int	reading_child_process(int file_descriptors[], t_command *cmd2, char **envp)
{
	dup2(file_descriptors[0], STDIN_FILENO);
	close(file_descriptors[0]);
	close(file_descriptors[1]);
	execve(cmd2->cmd_path, cmd2->cmd_argv, envp);
	return (1);
}

int	create_pipe(int fds[], t_command *cmd1, t_command *cmd2, char **envp)
{
	int	pid_fork1;
	int	pid_fork2;

	if (pipe(fds) == -1)
		return (1);
	pid_fork1 = fork();
	if (pid_fork1 == -1)
		return (2);
	if (pid_fork1 == 0)
		writing_child_process(fds, cmd1, envp);
	pid_fork2 = fork();
	if (pid_fork2 == -1)
		return (2);
	if (pid_fork2 == 0)
		reading_child_process(fds, cmd2, envp);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid_fork1, NULL, 0);
	waitpid(pid_fork2, NULL, 0);
	return (0);
}

int	main(int argc, char **argv, char *envp[])
{
	t_command	cmd1;
	t_command	cmd2;
	int			files[2];

	if (argc == 5)
	{
		cmd1.cmd_argv = &argv[2];
		cmd2.cmd_argv = &argv[3];
		parse_command(argv[2], envp, &cmd1);
		parse_command(argv[3], envp, &cmd2);
		files[0] = open(argv[1], O_WRONLY);
		files[1] = open(argv[4], O_WRONLY);
		create_pipe(files, &cmd1, &cmd2, envp);
	}
	return (0);
}
