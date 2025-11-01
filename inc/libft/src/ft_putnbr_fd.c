/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:01:25 by mkling            #+#    #+#             */
/*   Updated: 2024/05/31 17:11:56 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num = num * -1;
	}
	if (num <= 9)
		ft_putchar_fd(('0' + num), fd);
	if (num > 9)
	{
		ft_putnbr_fd((num / 10), fd);
		ft_putchar_fd('0' + (num % 10), fd);
	}
}
