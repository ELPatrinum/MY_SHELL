/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:01:42 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/11 12:57:41 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_star(char *word, int *count)
{
	char	*res;
	char	*tmp;
	DIR		*dir;

	(*count) = 0;
	dir = opendir(".");
	res = check_and_join(word, count, dir);
	closedir(dir);
	if (!res)
		return (NULL);
	tmp = ft_strtrim(res, " ");
	free(res);
	res = tmp;
	if (!res)
		return (NULL);
	if (!ft_strlen(res))
		return (free(res), ft_strdup(word));
	return (res);
}
