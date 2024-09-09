/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:07:05 by mkling            #+#    #+#             */
/*   Updated: 2024/09/08 21:21:23 by mkling           ###   ########.fr       */
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

enum e_file_type {
	READ = 0,
	WRITE = 1,
	APPEND = 2,
	TMP = 3,
};

enum e_typical_argv_index {
	PROGRAM_NAME = 0,
	INFILE = 1,
	CMD_1 = 2,
	CMD_2 = 3,
	OUTFILE = 4,
};

enum e_heredoc_argv_index {
	H_PROGRAM_NAME = 0,
	H_HERE_DOC = 1,
	H_LIMITER = 2,
	H_CMD_1 = 3,
	H_CMD_2 = 4,
	H_OUTFILE = 5,
};

char	**get_cmd_argv(char *cmd_string);
char	*get_cmd_path(char *cmd, char **envp);
int		is_last_command(int *pipe_fd);
int		redirect(int newfd, int oldfd);
int		open_file(char *filepath, int mode);
int		create_pipe_and_fork(int *pipe_fd, pid_t *fork_pid);
int		close_and_wait_for_fork(int *pipe_fd, int fork_pid);
int		adjust_for_heredoc(int argc, char **argv, char **envp);
void	free_array(char **array);
int		main(int argc, char **argv, char *envp[]);

#endif
