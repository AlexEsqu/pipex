/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_buffering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:57:23 by mkling            #+#    #+#             */
/*   Updated: 2024/08/14 11:16:05 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	init_buff(t_buffer *buffer)
{
	buffer->size = 420;
	buffer->total = 0;
	buffer->data = ft_calloc(buffer->size, sizeof(*buffer->data));
	if (!buffer->data)
	{
		buffer->data = NULL;
		return (MALLOC_ERROR);
	}
	ft_memset(buffer->data, '\0', sizeof(*buffer->data));
	buffer->used = 0;
	return (OK);
}

void	flush_buff(t_buffer *buffer)
{
	write(1, buffer->data, buffer->used);
	buffer->total += buffer->used;
	buffer->used = 0;
}

int	putchar_buff_idx(const char *format, size_t *ptr_index, t_buffer *buffer)
{
	if (!format || !buffer || !ptr_index)
		return (OK);
	if (buffer->used == buffer->size)
		flush_buff(buffer);
	buffer->data[buffer->used] = format[*ptr_index];
	*ptr_index = *ptr_index + 1;
	buffer->used++;
	return (OK);
}

int	putchar_to_buff(char c, t_buffer *buffer)
{
	if (buffer->used == buffer->size)
		flush_buff(buffer);
	buffer->data[buffer->used] = c;
	buffer->used++;
	return (OK);
}

int	putstr_to_buff(char *str, t_buffer *buffer)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		putchar_to_buff(str[index], buffer);
		index++;
	}
	return (OK);
}
