/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parsing_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:11:06 by mkling            #+#    #+#             */
/*   Updated: 2024/08/14 11:08:22 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		putchar_to_buff(char c, t_buffer *buffer);

void	putnbr_base_to_buff(long long num, char *base, t_buffer *buffer)
{
	long long	size;

	size = ft_strlen(base);
	if (num < 0)
	{
		putchar_to_buff('-', buffer);
		num = num * -1;
	}
	if (num < size)
		putchar_to_buff(base[num % size], buffer);
	if (num >= size)
	{
		putnbr_base_to_buff((num / size), base, buffer);
		putchar_to_buff(base[num % size], buffer);
	}
}

int	parse_unsign(t_buffer *buffer, unsigned int num)
{
	putnbr_base_to_buff(num, DECIMAL, buffer);
	return (OK);
}

int	parse_int(t_buffer *buffer, int num)
{
	putnbr_base_to_buff(num, DECIMAL, buffer);
	return (OK);
}

int	parse_hex_low(t_buffer *buffer, unsigned long num)
{
	putnbr_base_to_buff(num, LOWER_HEXA, buffer);
	return (OK);
}

int	parse_hex_up(t_buffer *buffer, unsigned long num)
{
	putnbr_base_to_buff(num, UPPER_HEXA, buffer);
	return (OK);
}
