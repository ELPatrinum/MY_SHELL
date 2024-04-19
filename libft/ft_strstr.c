/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:04:23 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/10 18:54:10 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char		*p1;
	char		*p1_start;
	const char	*p2;

	if (*needle == '\0')
		return ((char *)haystack);
	p1 = (char *)haystack;
	while (*p1 != '\0')
	{
		p1_start = p1;
		p2 = needle;
		while (*p1 != '\0' && *p2 != '\0' && *p1 == *p2)
		{
			p1++;
			p2++;
		}
		if (*p2 == '\0')
			return (p1_start);
		p1 = p1_start + 1;
	}
	return (NULL);
}
