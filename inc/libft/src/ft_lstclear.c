/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:31:39 by mkling            #+#    #+#             */
/*   Updated: 2024/06/02 13:35:04 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p_next;
	t_list	*p_current;

	p_current = *lst;
	while (p_current != NULL)
	{
		p_next = p_current->next;
		ft_lstdelone(p_current, del);
		p_current = p_next;
	}
	*lst = NULL;
}
