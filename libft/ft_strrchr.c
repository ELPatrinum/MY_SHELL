/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:16:44 by muel-bak          #+#    #+#             */
/*   Updated: 2023/11/03 20:32:37 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	c2;
	char	*location;
	int		i;

	c2 = (char)c;
	location = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c2)
			location = ((char *)(s + i));
		i++;
	}
	if (s[i] == c2)
		location = ((char *)(s + i));
	return (location);
}
