/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:05:41 by mkling            #+#    #+#             */
/*   Updated: 2024/09/16 10:15:53 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	assemble_heredoc(char *limiter)
{
	int		heredoc_fd;
	char	*result;

	heredoc_fd = open_file(HEREDOC_FILEPATH, WRITE);
	if (heredoc_fd == -1)
		return (perror("Unable to create temp heredoc"), -1);
	while (1)
	{
		write(STDIN_FILENO, "heredoc> ", 9);
		result = get_next_line(STDIN_FILENO);
		if (ft_strncmp(limiter, result, ft_strlen(limiter)) == 0)
			break ;
		write(heredoc_fd, result, ft_strlen(result));
	}
	close(heredoc_fd);
	return (OK);
}


