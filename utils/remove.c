/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:19:05 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/12 11:26:27 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_char(char *str, char c)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		res = append_char(res, str[i]);
		i++;
	}
	free(str);
	return (res);
}
