/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:27:18 by muel-bak          #+#    #+#             */
/*   Updated: 2023/11/06 23:27:18 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*node;

	newlist = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	while (lst)
	{
		node = malloc (sizeof * node);
		if (!node)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		node->next = NULL;
		node->content = f(lst->content);
		ft_lstadd_back(&newlist, node);
		lst = lst->next;
	}
	return (newlist);
}
