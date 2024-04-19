/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:51:12 by muel-bak          #+#    #+#             */
/*   Updated: 2023/11/07 15:43:39 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elements, size_t size)
{
	void	*res;

	if (size && elements > (4294967295 / size))
		return (NULL);
	res = malloc(elements * size);
	if (!res)
		return (NULL);
	ft_bzero(res, elements * size);
	return (res);
}
