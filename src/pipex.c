/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:59:07 by mkling            #+#    #+#             */
/*   Updated: 2024/09/13 19:46:05 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_syntax(int argc, char **argv)
{
	if (argc < 5)
	{
		perror("Invalid number of arguments");
		exit(SYNTAX_ERROR);
	}
	if (argc < 6 && ft_strcmp(argv[INFILE], "HERE_DOC") == 0)
	{
		perror("Invalid arguments for here_doc"),
		exit(SYNTAX_ERROR);
	}
	return (OK);
}

static int	connect_pipe(int pipe_fd[], t_index *index)
{
	if (is_last_cmd(index))
		return (replace_stdout_by_outfile(index->outfile));
	if (is_first_cmd(index))
		return (re_stdin_by_infile_stdout_by_pipe(index, pipe_fd));
	return (replace_stdout_by_pipe_write(pipe_fd));
}

static int	exec_cmd(int pipe_fd[], t_index *index)
{
	t_cmd	*cmd;

	if (connect_pipe(pipe_fd, index) != OK)
		exit(index->exit_code);
	cmd = get_cmd(index);
	if (!cmd)
		exit(index->exit_code);
	execve(cmd->cmd_path, cmd->cmd_argv, index->envp);
	return (perror("Failed command"), CANT_EXECUTE_CMD);
}

static int	wait_on_all_forks(int fork_pid, t_index *index)
{
	int	exit_code;

	exit_code = 0;
	waitpid(fork_pid, &exit_code, 0);
	exit_code = WEXITSTATUS(exit_code);
	waitpid(-1, 0, WNOHANG);
	if (index->heredoc_flag)
		unlink(HEREDOC_FILEPATH);
	return (exit_code);
}

int	main(int argc, char **argv, char *envp[])
{
	int		pipe_fd[2];
	int		fork_pid;
	t_index	*index;

	check_syntax(argc, argv);
	index = create_index(argc, argv, envp);
	while (index->current_cmd <= index->last_cmd)
	{
		if (create_pipe(pipe_fd, index) != OK)
			return (PIPE_ERROR);
		if (create_fork(&fork_pid) != OK)
			return (FORK_ERROR);
		if (fork_pid == IS_FORK)
			exec_cmd(pipe_fd, index);
		if (close_pipe(pipe_fd, index) != OK)
			return (DUP_ERROR);
		index->current_cmd++;
	}
	free_index(index);
	return (wait_on_all_forks(fork_pid, index));
}
