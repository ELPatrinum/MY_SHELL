/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:55:08 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 16:56:16 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_lex_null(t_lex **list)
{
	free_lex_list(list);
	*list = NULL;
}

void	append_node(t_lex **list, char **line)
{
	t_type	type;
	t_lex	*new;
	t_lex	*tmp;

	if (!list)
		return ;
	new = (t_lex *) malloc(sizeof(t_lex));
	if (!new)
		return (free_lex_null(list));
	type = TOKEN_EXEC;
	new->content = get_content(line, &type);
	if (!(new->content))
		return (free(new));
	new->node_type = type;
	new->next = NULL;
	if (!(*list))
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_lex	*lex_line(char **line)
{
	t_lex	*res;

	if (!line)
		return (NULL);
	res = NULL;
	while (*line && ft_strlen(*line))
	{
		append_node(&res, line);
		if (!res)
			return (NULL);
	}
	return (res);
}
