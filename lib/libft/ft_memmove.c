/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:45:51 by mkling            #+#    #+#             */
/*   Updated: 2024/05/30 12:37:48 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*strsrc;
	unsigned char	*strdest;

	i = 0;
	strsrc = (unsigned char *)src;
	strdest = (unsigned char *)dest;
	if (dest > src)
	{
		while (len > 0)
		{
			len--;
			strdest[len] = strsrc[len];
		}
	}
	else if (dest < src)
	{
		while (i < len)
		{
			strdest[i] = strsrc[i];
			i++;
		}
	}
	return (dest);
}
