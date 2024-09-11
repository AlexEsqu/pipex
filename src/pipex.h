/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:07:05 by mkling            #+#    #+#             */
/*   Updated: 2024/09/11 12:22:21 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "../lib/libft/libft.h"

# define IS_FORK 0
# define HEREDOC_FILEPATH "tmp/.heredoc"

enum e_exit_num {
	FAIL = -1,
	OK = 0,
	GENERAL_ERROR = 1,
	PIPE_ERROR = 1,
	CANT_OPEN_FILE = 1,
	CMD_IS_DIRECTORY = 126,
	CANT_FIND_CMD = 127,
};

enum e_file_type {
	READ = 0,
	WRITE = 1,
	HEREDOC_READ = 2,
	HEREDOC_WRITE = 3,
	APPEND = 4,
	TMP = 5,
};

enum e_typical_argv_index {
	PROGRAM_NAME = 0,
	INFILE = 1,
	CMD_1 = 2,
	CMD_2 = 3,
	OUTFILE = 4,
};

// PARSING
char	**get_cmd_argv(char *cmd_string);
char	*get_cmd_path(char *cmd, char **envp);
int		check_commands(char **argv, char **envp, int argc);

// READABILITY
int		is_last_cmd(char **argv, int cmd_index);
int		redirect(int newfd, int oldfd);
int		open_file(char *filepath, int mode);
int		create_pipe(int *pipe_fd, char **argv, int cmd_index);
int		create_fork(pid_t *fork_pid);
int		close_pipe(int *pipe_fd, char **argv, int cmd_index);
int		is_directory(char *cmd);

// HEREDOC
int		adjust_for_heredoc(int argc, char **argv, char **envp);
int		main(int argc, char **argv, char *envp[]);

#endif
