/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:58:50 by muel-bak          #+#    #+#             */
/*   Updated: 2023/11/01 17:48:33 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*src2;
	char	*dest2;

	src2 = (char *)src;
	dest2 = (char *)dest;
	if (dest > src)
	{
		while (len > 0)
		{
			dest2[len - 1] = src2[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}
