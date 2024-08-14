/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:16:19 by mkling            #+#    #+#             */
/*   Updated: 2024/05/22 15:51:45 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *ptr, int value, unsigned long len)
{
	unsigned char	*str;

	str = ptr;
	while (len--)
		*str++ = (unsigned char)value;
	return (ptr);
}
