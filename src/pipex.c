/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:59:07 by mkling            #+#    #+#             */
/*   Updated: 2024/08/15 19:58:19 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char *envp[])
{
	char	*cmd1;
	char	*cmd2;
	char	infile;
	char	outfile;

	if (argc == 5)
	{
		cmd1 = find_cmd_path(argv[2], envp);
		cmd2 = find_cmd_path(argv[3], envp);
		infile = open(argv[1], O_WRONLY);
		execve(argv[0], &cmd1, envp);
		outfile = open(argv[4], O_WRONLY);
		execve(argv[0], &cmd2, envp);
	}
	return (0);
}
