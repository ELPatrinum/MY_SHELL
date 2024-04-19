/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:03:43 by muel-bak          #+#    #+#             */
/*   Updated: 2023/11/02 15:06:19 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	char		*d;
	const char	*s = src;
	size_t		i;

	d = dest;
	i = 0;
	if (size > 0)
	{
		while (i < (size - 1) && s[i] != '\0')
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
	}
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
