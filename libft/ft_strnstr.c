/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:08:25 by mkling            #+#    #+#             */
/*   Updated: 2024/05/30 19:22:40 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	if (!*haystack)
		return (NULL);
	while (i < len)
	{
		if ((i + needle_len) > len)
			return (NULL);
		if (haystack[i] == needle[0]
			&& (ft_strncmp(needle, &haystack[i], needle_len) == 0))
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
