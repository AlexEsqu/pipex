/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:26:33 by mkling            #+#    #+#             */
/*   Updated: 2024/06/01 13:28:06 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*iteri;

	i = 0;
	if (lst == NULL)
		return (0);
	iteri = lst;
	while (iteri != NULL)
	{
		iteri = iteri->next;
		i++;
	}
	return (i);
}
