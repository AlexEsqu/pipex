/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:17:41 by mkling            #+#    #+#             */
/*   Updated: 2024/08/14 11:25:08 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "ft_printf.h"

int		init_buff(t_buffer *buffer);
void	flush_buff(t_buffer *buffer);
int		parse_int(t_buffer *buffer, int num);
int		parse_str( t_buffer *buffer, char *string);
int		parse_char(t_buffer *buffer, int num);
int		parse_ptr(t_buffer *buffer, uintptr_t pointer);
int		parse_perc(t_data_format *profile, t_buffer *buffer);
int		parse_unsign(t_buffer *buffer, unsigned int num);
int		parse_hex_low(t_buffer *buffer, unsigned long num);
int		parse_hex_up(t_buffer *buffer, unsigned long num);
int		putchar_buff_idx(const char *format, size_t *ptr_index,
			t_buffer *buffer);

static int	set_format(t_data_format *data_format,
	t_buffer *buffer, va_list arg_list)
{
	if (data_format->specifier == 'c')
		return (parse_char(buffer, va_arg(arg_list, int)));
	if (data_format->specifier == 'p')
		return (parse_ptr(buffer, va_arg(arg_list, uintptr_t)));
	if (data_format->specifier == 'd' || data_format->specifier == 'i')
		return (parse_int(buffer, va_arg(arg_list, int)));
	if (data_format->specifier == 'u')
		return (parse_unsign(buffer, va_arg(arg_list, unsigned int)));
	if (data_format->specifier == 'x')
		return (parse_hex_low(buffer, va_arg(arg_list, unsigned int)));
	if (data_format->specifier == 'X')
		return (parse_hex_up(buffer, va_arg(arg_list, unsigned int)));
	if (data_format->specifier == 's')
		return (parse_str(buffer, va_arg(arg_list, char *)));
	else if (ft_isprint(data_format->specifier))
		return (parse_perc(data_format, buffer));
	else
		return (WRITING_ERROR);
}

static void	set_spec(const char *format, size_t *formaindex,
	t_data_format *data_format)
{
	data_format->specifier = format[*formaindex];
	*formaindex = *formaindex + 1;
}

static int	set_print(const char *format, size_t *formaindex,
	va_list arg_list, t_buffer *buffer)
{
	t_data_format	data_format;

	while (format[*formaindex])
	{
		if (format[*formaindex] == '%')
		{
			ft_memset(&data_format, 0, sizeof(data_format));
			*formaindex = *formaindex + 1;
			set_spec(format, formaindex, &data_format);
			set_format(&data_format, buffer, arg_list);
		}
		else
			putchar_buff_idx(format, formaindex, buffer);
	}
	flush_buff(buffer);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list			arg_list;
	t_buffer		buffer;
	size_t			index;

	index = 0;
	init_buff(&buffer);
	va_start(arg_list, format);
	if (!format)
		return (-1);
	set_print(format, &index, arg_list, &buffer);
	va_end(arg_list);
	free(buffer.data);
	buffer.data = NULL;
	return (buffer.total);
}
