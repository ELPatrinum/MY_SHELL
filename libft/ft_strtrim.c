/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:24:28 by muel-bak          #+#    #+#             */
/*   Updated: 2023/11/07 15:53:44 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_string(void)
{
	char	*empty_str;

	empty_str = malloc(1);
	if (empty_str != NULL)
		empty_str[0] = '\0';
	return (empty_str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed;
	int		first;
	int		last;

	first = 0;
	last = ft_strlen(s1) - 1;
	while (first <= last && ft_strchr(set, s1[first]))
		first++;
	if (first > last)
		return (empty_string());
	while (last >= 0 && ft_strchr(set, s1[last]))
		last--;
	trimed = malloc((last - first) + 2);
	if (trimed == NULL)
		return (NULL);
	ft_strlcpy(trimed, &s1[first], last - first + 2);
	return (trimed);
}
