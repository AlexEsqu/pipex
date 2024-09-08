/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:52:36 by mkling            #+#    #+#             */
/*   Updated: 2024/09/08 18:00:48 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	accumulate_here_doc(char *limiter)
{
	char	*result;

	if (redirect(open_file("tmp/.heredoc", TMP), STDIN_FILENO) == -1)
		return (-1);
	while (strcmp(result, limiter) != 0)
	{

	}
	return (0);
}

int	here_doc_pipex(char **argv, char **envp)
{
	accumulate_here_doc(argv[H_LIMITER]);
	modify_argv();
	main();
}


