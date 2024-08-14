/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:17:33 by mkling            #+#    #+#             */
/*   Updated: 2024/08/14 11:25:41 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define BUFFER_SIZE 420
# define FLAGS "0. #-+"
# define SPECIFIERS "csdiupxX%%"
# define LOWER_HEXA "0123456789abcdef"
# define UPPER_HEXA "0123456789ABCDEF"
# define DECIMAL "0123456789"

# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_data_format
{
	char		specifier;
	int			f_left;
	int			f_plus;
	int			f_blank;
	int			f_zero;
	int			f_alt_form;
}	t_data_format;

typedef struct s_buffer
{
	size_t	size;
	size_t	used;
	char	*data;
	size_t	total;
}	t_buffer;

typedef enum e_errortype
{
	OK = 0,
	MALLOC_ERROR = -1,
	WRITING_ERROR = -2,
	READING_ERROR = -3,
	UNSUPPORTED = -4
}	t_errornum;

int		ft_printf(const char *format, ...);

#endif
