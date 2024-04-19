/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:47:21 by muel-bak          #+#    #+#             */
/*   Updated: 2023/11/08 09:40:30 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static int	is_it_acopy(size_t indx, const char *h, const char *n)
{
	size_t	j;

	j = 0;
	while (n[j] != '\0' && h[indx] == n[j])
	{
		j++;
		indx++;
	}
	if (n[j] == '\0')
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle,
		size_t haystacklen)
{
	size_t		i;
	const char	*p = NULL;
	size_t		remaining;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < haystacklen)
	{
		if (haystack[i] == needle[0])
		{
			remaining = haystacklen - i;
			if (remaining >= ft_strlen(needle) && is_it_acopy(i, haystack,
					needle))
			{
				p = &haystack[i];
				break ;
			}
		}
		i++;
	}
	return ((char *)p);
}
