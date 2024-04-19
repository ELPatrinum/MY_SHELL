/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:28:02 by muel-bak          #+#    #+#             */
/*   Updated: 2023/11/01 21:56:15 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	const unsigned char	*p;
	unsigned char		v;

	p = ptr;
	v = (unsigned char)value;
	while (num > 0)
	{
		if (*p == v)
			return ((void *)p);
		p++;
		num--;
	}
	return (NULL);
}
