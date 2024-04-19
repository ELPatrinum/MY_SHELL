/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:22:14 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 16:56:12 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_type(char *res, t_type *type)
{
	if (!ft_strncmp(res, "||", 2))
		*type = TOKEN_OR;
	else if (!ft_strncmp(res, "|", 1))
		*type = TOKEN_PIPE;
	else if (!ft_strncmp(res, "&&", 2))
		*type = TOKEN_AND;
	else if (!ft_strncmp(res, "(", 1))
		*type = TOKEN_BRKT_OPEN;
	else if (!ft_strncmp(res, ")", 1))
		*type = TOKEN_BRKT_CLOSE;
	else if (!ft_strncmp(res, "<<", 2))
		*type = TOKEN_HEREDOC;
	else if (!ft_strncmp(res, ">>", 2))
		*type = TOKEN_REDIR_APPEND;
	else if (!ft_strncmp(res, ">", 1))
		*type = TOKEN_REDIR_OUT;
	else if (!ft_strncmp(res, "<", 1))
		*type = TOKEN_REDIR_IN;
	else
		*type = 0;
}

char	*eval_next_string(char *res, char **line, t_type *type, char *tokens)
{
	char	*tmp;

	if (!res)
		return (NULL);
	if (ft_strchr("\"\'", **line))
		return (eval_next_quotes(line, res, type, tokens));
	tmp = eval_string(line, type, tokens);
	res = (ft_strjoin(res, tmp));
	return (free(tmp), res);
}

char	*eval_next_quotes(char **line, char *res, t_type *type, char *tokens)
{
	char	*tmp;
	char	*tmp_join;

	if (!res)
		return (NULL);
	tmp = eval_quotes(line, type, tokens);
	tmp_join = ft_strjoin(res, tmp);
	return (free(tmp), tmp_join);
}

char	*advance_append(char *str, char *res, int *i)
{
	char	symbol;

	symbol = *str;
	while (str[*i] && str[*i] != symbol)
	{
		res = append_char(res, str[*i]);
		if (!res)
			return (NULL);
		(*i)++;
	}
	return (res);
}
