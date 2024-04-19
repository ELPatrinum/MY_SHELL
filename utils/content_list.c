/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:35:40 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/12 11:26:09 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_content	*get_content_node(char *str, t_type type)
{
	t_content	*new;

	new = (t_content *) malloc(sizeof(t_content));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->str = str;
	new->node_type = type;
	return (new);
}

void	append_content_node(t_content **content, char *str, t_type type)
{
	t_content	*new;
	t_content	*tmp;

	new = get_content_node(str, type);
	if (!new)
	{
		free_content_list(*content);
		*content = NULL;
		return ;
	}
	if (!(*content))
	{
		*content = new;
		return ;
	}
	tmp = *content;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

char	*get_content(char **line, t_type *type)
{
	char	*tmp;
	char	*tokens;
	int		i;

	tokens = "<>|&()";
	i = 0;
	tmp = *line;
	while (tmp[i] && ft_isspace(tmp[i]))
		i++;
	*line = tmp + i;
	if (!tmp[i])
		return (NULL);
	if (tmp[i] == '\'' || tmp[i] == '\"')
		return (eval_quotes(line, type, tokens));
	if (ft_strchr(tokens, tmp[i]))
		return (eval_symbols(line, type));
	return (eval_string(line, type, tokens));
}
