/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parsing_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:45:23 by mkling            #+#    #+#             */
/*   Updated: 2024/08/14 11:13:35 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		putchar_to_buff(char c, t_buffer *buffer);
int		putstr_to_buff(char *str, t_buffer *buffer);
void	putnbr_base_to_buff(long long num, char *base, t_buffer *buffer);

int	parse_str(t_buffer *buffer, char *string)
{
	if (string == NULL)
		putstr_to_buff("(null)", buffer);
	else
		putstr_to_buff(string, buffer);
	return (OK);
}

int	parse_char(t_buffer *buffer, int character)
{
	putchar_to_buff((char)character, buffer);
	return (OK);
}

int	parse_ptr(t_buffer *buffer, uintptr_t pointer)
{
	uintptr_t	size;

	if (!pointer)
		putstr_to_buff("(nil)", buffer);
	else
	{
		putstr_to_buff("0x", buffer);
		size = ft_strlen(LOWER_HEXA);
		if (pointer < size)
			putchar_to_buff(LOWER_HEXA[pointer % size], buffer);
		if (pointer >= size)
		{
			putnbr_base_to_buff((pointer / size), LOWER_HEXA, buffer);
			putchar_to_buff(LOWER_HEXA[pointer % size], buffer);
		}
	}
	return (OK);
}

int	parse_perc(t_data_format *data_format, t_buffer *buffer)
{
	if (data_format->specifier == '%')
		putchar_to_buff('%', buffer);
	if (data_format->specifier != '%')
	{
		putchar_to_buff('%', buffer);
		putchar_to_buff(data_format->specifier, buffer);
	}
	return (OK);
}
