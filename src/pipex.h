/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:07:05 by mkling            #+#    #+#             */
/*   Updated: 2024/08/19 11:17:37 by mkling           ###   ########.fr       */
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
# include "../lib/libftprintf/ft_printf.h"

enum e_file_type {
	READ = 0,
	WRITE = 1
};

enum e_argv_index {
	PROGRAM_NAME = 0,
	INFILE = 1,
	CMD_1 = 2,
	CMD_2 = 3,
	OUTFILE = 4,
};
typedef struct s_command {
	char	**cmd_argv;
	char	*cmd_stem;
	char	*cmd_path;
}	t_command;

int		parse_cmd(char *cmd_line, char **envp, t_command *cmd);
void	free_cmd(t_command *cmd);

#endif
