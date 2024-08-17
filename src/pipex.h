/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:07:05 by mkling            #+#    #+#             */
/*   Updated: 2024/08/17 13:17:41 by mkling           ###   ########.fr       */
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

typedef struct s_command {
	char	**cmd_argv;
	char	*cmd_stem;
	char	*cmd_path;
}	t_command;

int	parse_command(char *cmd_line, char **envp, t_command *cmd);

#endif
