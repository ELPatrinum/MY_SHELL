/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:21:12 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 11:30:59 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_type(t_type *type, char symbol)
{
	if (*type != TOKEN_D_Q && *type != TOKEN_S_Q)
	{
		*type = TOKEN_D_Q;
		if (symbol == '\'')
			*type = TOKEN_S_Q;
	}
}

static int	init_vars(char **tmp, char **res, char **line, int *i)
{
	*tmp = *line;
	*i = 0;
	if ((*tmp)[0])
		(*i)++;
	*res = ft_strdup("");
	if (!(*res))
		return (0);
	return (1);
}

char	*eval_quotes(char **line, t_type *type, char *tokens)
{
	char	*res;
	char	*tmp;
	char	symbol;
	int		i;

	if (!line)
		return (NULL);
	symbol = **line;
	set_type(type, symbol);
	if (!init_vars(&tmp, &res, line, &i))
		return (NULL);
	res = advance_append(tmp, res, &i);
	*line = tmp + i;
	if (!tmp[i] || !res)
		return (free(res), NULL);
	i++;
	*line = tmp + i;
	if (symbol == '\'')
		res = append_char(res, 3);
	else
		res = append_char(res, 4);
	if (tmp && !ft_isspace(tmp[i]) && !ft_strchr(tokens, tmp[i]))
		return (eval_next_string(res, line, type, tokens));
	return (res);
}

char	*eval_symbols(char **line, t_type *type)
{
	char	*res;
	char	*tmp;
	int		i;

	tmp = *line;
	i = 0;
	if (!tmp[i])
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	*type = -1;
	if (ft_strchr("<>|&", tmp[i]))
	{
		res = append_char(res, tmp[i++]);
		if (res && tmp[i] == tmp[i - 1])
			res = append_char(res, tmp[i++]);
	}
	else
		res = append_char(res, tmp[i++]);
	if (!res)
		return (NULL);
	*line = tmp + i;
	assign_type(res, type);
	return (res);
}

char	*eval_string(char **line, t_type *type, char *tokens)
{
	char	*res;
	char	*tmp;
	int		i;

	*type = TOKEN_EXEC;
	tmp = *line;
	i = 0;
	while (tmp[i] && !ft_strchr("\'\"", tmp[i])
		&& !ft_strchr(tokens, tmp[i]))
	{
		if (*type != TOKEN_D_Q && *type != TOKEN_S_Q && ft_isspace(tmp[i]))
			break ;
		i++;
	}
	*line = tmp + i;
	res = ft_substr(tmp, 0, i);
	if (!res)
		return (NULL);
	res = append_char(res, 5);
	if (!res)
		return (NULL);
	if (tmp[i] == '\'' || tmp[i] == '\"')
		return (eval_next_quotes(line, res, type, tokens));
	return (res);
}
