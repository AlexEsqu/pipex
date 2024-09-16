/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:07:05 by mkling            #+#    #+#             */
/*   Updated: 2024/09/16 10:06:27 by mkling           ###   ########.fr       */
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

typedef struct s_index {
	int				argc;
	char			**argv;
	char			**envp;
	char			**extracted_paths;
	char			*infile;
	char			*outfile;
	int				current_cmd;
	int				last_cmd;
	int				exit_code;
	int				heredoc_flag;
}	t_index;

typedef struct s_cmd {
	char			*cmd_path;
	char			**cmd_argv;
	int				cmd_index;
	int				cmd_exit_code;
}	t_cmd;

enum e_exit_num {
	FAIL = -1,
	INVALID_FD = -1,
	OK = 0,
	MALLOC_FAIL = 1,
	GENERAL_ERROR = 1,
	SYNTAX_ERROR = 1,
	PIPE_ERROR = 1,
	FORK_ERROR = 1,
	DUP_ERROR = 1,
	NO_FILE = 1,
	READ_ERROR = 1,
	OPEN_ERROR = 1,
	CANT_EXECUTE_CMD = 126,
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
	HEREDOC_LIMITER = 2,
	CMD_1 = 2,
	CMD_2 = 3,
	OUTFILE = 4,
};

// PARSING
t_cmd	*get_cmd(t_index *index);
int		check_cmd(t_cmd *cmd, t_index *index);
int		free_cmd_then_exit(t_cmd *cmd, char *emess, int errnum, t_index *index);

// INDEXING
t_index	*create_index(int argc, char **argv, char **envp);
int		extract_if_path_variable(t_index *index);
int		free_index(t_index *index);

// READABILITY
int		is_first_cmd(t_index *index);
int		is_last_cmd(t_index *index);
int		redirect(int newfd, int oldfd);
int		open_file(char *filepath, int mode);
int		create_pipe(int *pipe_fd, t_index *index);
int		create_fork(pid_t *fork_pid, t_index *index);
int		close_pipe(int *pipe_fd, t_index *index);
int		is_directory(char *cmd);

// CONNECTING PIPES
int		replace_stdout_by_outfile(char *outfilepath);
int		re_stdin_by_infile_stdout_by_pipe(t_index *index, int *pipe_fd);
int		replace_stdout_by_pipe_write(int pipe_fd[]);

// HEREDOC
int		assemble_heredoc(char *limiter);

#endif
