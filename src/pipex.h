/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:07:05 by mkling            #+#    #+#             */
/*   Updated: 2024/09/04 17:02:40 by mkling           ###   ########.fr       */
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
	WRITE = 1
};

enum e_pipe_type {
	CURRENT = 0,
	PREVIOUS = 1
};

enum e_argv_index {
	PROGRAM_NAME = 0,
	INFILE = 1,
	CMD_1 = 2,
	CMD_2 = 3,
	OUTFILE = 4,
};

char	**get_cmd_argv(char *cmd_string);
char	*get_cmd_path(char *cmd, char **envp);
int		is_even(int num);
int		is_last_command(int cmd_index, int argc);
int		is_first_command(int cmd_index);
int		redirect(int newfd, int oldfd);

#endif
