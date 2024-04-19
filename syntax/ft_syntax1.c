/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:39:06 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/20 00:56:48 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_parenthese(t_tok *head, int *heredoc)
{
	t_tok	*current;

	current = head;
	if (head == NULL || head->next == NULL)
		return (true);
	while (current->next != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
			(*heredoc)++;
		if ((current->type == TOKEN_EXPR
				&& current->next->type == TOKEN_BRKT_OPEN)
			|| (current->type == TOKEN_BRKT_CLOSE
				&& current->next->type == TOKEN_EXPR)
			|| (current->type == TOKEN_BRKT_OPEN
				&& current->next->type == TOKEN_PIPE
				&& current->next->type == TOKEN_AND
				&& current->next->type == TOKEN_OR)
			|| (current->type != TOKEN_EXPR
				&& current->type != TOKEN_BRKT_CLOSE
				&& current->next->type == TOKEN_BRKT_CLOSE))
			return (false);
		current = current->next;
	}
	return (true);
}

bool	check_redir_in_out(t_tok *head, int *heredoc)
{
	t_tok	*current;

	current = head;
	if (head == NULL || head->next == NULL)
		return (true);
	while (current->next != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
			(*heredoc)++;
		if ((current->type == TOKEN_REDIR_IN
				|| current->type == TOKEN_REDIR_OUT
				|| current->type == TOKEN_HEREDOC
				|| current->type == TOKEN_REDIR_APPEND)
			&& (current->next->type == TOKEN_REDIR_IN
				|| current->next->type == TOKEN_REDIR_OUT
				|| current->next->type == TOKEN_HEREDOC
				|| current->next->type == TOKEN_REDIR_APPEND))
			return (false);
		current = current->next;
	}
	if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
		|| current->type == TOKEN_HEREDOC)
		return (false);
	return (true);
}

bool	check_start_end_tokens(t_tok *head, int *heredoc)
{
	t_tok	*current;

	current = head;
	if (head == NULL)
		return (false);
	if (head->type == TOKEN_PIPE || head->type == TOKEN_AND
		|| head->type == TOKEN_OR)
		return (false);
	while (current->next != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
			(*heredoc)++;
		if (!ft_strncmp(current->value, ">>>", ft_strlen(">>>")))
			return (false);
		current = current->next;
	}
	if (current->type == TOKEN_PIPE || current->type == TOKEN_AND
		|| current->type == TOKEN_OR || current->type == TOKEN_REDIR_IN
		|| current->type == TOKEN_REDIR_OUT
		|| current->type == TOKEN_HEREDOC
		|| current->type == TOKEN_REDIR_APPEND)
		return (false);
	return (true);
}

bool	closed_quotes(char *str)
{
	bool	closed;
	bool	inside;
	char	type;

	closed = true;
	inside = false;
	type = '\0';
	if (!str || !*str)
		return (true);
	while (*str != '\0')
	{
		if (!inside && (*str == '\'' || *str == '\"'))
		{
			type = *str;
			closed = false;
			inside = true;
		}
		else if (inside && *str == type)
		{
			inside = false;
			closed = true;
		}
		str++;
	}
	return (closed);
}

bool	closed_parentheses(t_tok *head, int *heredoc)
{
	int	opend;

	opend = false;
	if (head == NULL)
		return (true);
	while (head)
	{
		if (head->type == TOKEN_HEREDOC)
			(*heredoc)++;
		if (head->type == TOKEN_BRKT_CLOSE && !opend)
			return (false);
		if (head->type == TOKEN_BRKT_OPEN)
			opend++;
		if (head->type == TOKEN_BRKT_CLOSE && opend)
			opend--;
		if (head->next)
			if (head->type == TOKEN_BRKT_OPEN
				&& head->next->type == TOKEN_BRKT_CLOSE)
				return (false);
		head = head->next;
	}
	if (opend)
		return (false);
	return (true);
}
