/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:32:06 by mkling            #+#    #+#             */
/*   Updated: 2024/05/30 12:33:26 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned long	i;
	unsigned char	*strsrc;
	unsigned char	*strdest;

	i = 0;
	strsrc = (unsigned char *)src;
	strdest = (unsigned char *)dest;
	if (src == dest)
		return (dest);
	while (len > i)
	{
		strdest[i] = strsrc[i];
		i++;
	}
	return ((void *)strdest);
}
