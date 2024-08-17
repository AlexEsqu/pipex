/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:59:07 by mkling            #+#    #+#             */
/*   Updated: 2024/08/17 15:00:11 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	reading_child_process(int fds[], t_command *cmd2, char **envp)
{
	if (dup2(fds[0], STDIN_FILENO) == -1)
	{
		perror("Error while duplicating infile to stdin");
		return (1);
	}
	close(fds[0]);
	close(fds[1]);
	execve(cmd2->cmd_path, cmd2->cmd_argv, envp);
	perror("Error while executing reading command");
	return (1);
}

int	writing_child_process(int fds[], t_command *cmd1, char **envp)
{
	if (dup2(fds[1], STDOUT_FILENO) == -1)
	{
		perror("Error while duplicating outfile to stdout");
		return (1);
	}
	close(fds[1]);
	close(fds[0]);
	execve(cmd1->cmd_path, cmd1->cmd_argv, envp);
	perror("Error while executing writing command");
	return (1);
}

int	create_pipe(int fds[], t_command *cmd1, t_command *cmd2, char **envp)
{
	int	pid_fork1;
	int	pid_fork2;

	if (pipe(fds) == -1)
	{
		perror("Error while creating pipe");
		return (1);
	}
	pid_fork1 = fork();
	if (pid_fork1 == 0)
		writing_child_process(fds, cmd1, envp);
	pid_fork2 = fork();
	if (pid_fork2 == 0)
		reading_child_process(fds, cmd2, envp);
	close(fds[0]);
	close(fds[1]);
	if (pid_fork1 == -1 || pid_fork2 == -1)
	{
		perror("Error while forking");
		return (1);
	}
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
		if (parse_cmd(argv[2], envp, &cmd1) == 1
			|| parse_cmd(argv[3], envp, &cmd2) == 1)
			return (1);
		files[0] = open(argv[1], O_RDONLY);
		files[1] = open(argv[4], O_WRONLY);
		if (files[0] == -1 || files[1] == -1)
		{
			perror("Error while opening files");
			return (1);
		}
		return (create_pipe(files, &cmd1, &cmd2, envp));
	}
	perror("Invalid number of arguments");
	return (1);
}
