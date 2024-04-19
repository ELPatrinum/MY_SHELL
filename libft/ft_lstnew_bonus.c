/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:40:26 by muel-bak          #+#    #+#             */
/*   Updated: 2023/11/06 19:40:26 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_t_list;

	new_t_list = (t_list *)malloc(sizeof(t_list));
	if (new_t_list == NULL)
		return (NULL);
	new_t_list->content = content;
	new_t_list->next = NULL;
	return (new_t_list);
}
