/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:34:31 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 16:56:24 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_type(t_type *type, char c)
{
	*type = TOKEN_S_Q;
	if (c == 4)
		*type = TOKEN_D_Q;
	else if (c == 5)
		*type = TOKEN_EXEC;
}

static int	set_tmp(char **tmp, char *content, int i, int start)
{
	*tmp = NULL;
	if (ft_strlen(content) == 1)
		(*tmp) = ft_strdup("");
	else
		(*tmp) = ft_substr(content, start, i - start);
	if (!(*tmp))
		return (0);
	return (1);
}

static void	init_vars(t_content **res, int *i, int *start)
{
	*res = NULL;
	*i = 0;
	*start = 0;
}

t_content	*eval_content(char *content)
{
	t_content	*res;
	t_type		type;
	char		*tmp;
	int			start;
	int			i;

	if (!content)
		return (NULL);
	init_vars(&res, &i, &start);
	while (content[i])
	{
		if (content[i] >= 3 && content[i] <= 5)
		{
			init_type(&type, content[i]);
			if (!set_tmp(&tmp, content, i, start))
				return (NULL);
			append_content_node(&res, tmp, type);
			if (!res)
				return (free(tmp), NULL);
			start = i + 1;
		}
		i++;
	}
	return (res);
}
