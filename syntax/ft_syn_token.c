/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syn_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:48:14 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/20 00:56:59 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_redir_before_bracket(t_tok *head, int *heredoc)
{
	t_tok	*current;

	current = head;
	while (current && current->next)
	{
		if (current->type == TOKEN_HEREDOC)
			(*heredoc)++;
		if ((current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
				|| current->type == TOKEN_REDIR_APPEND
				|| current->type == TOKEN_HEREDOC)
			&& current->next->type == TOKEN_BRKT_OPEN)
			return (false);
		current = current->next;
	}
	return (true);
}

bool	check_tokens(t_tok *head, int *heredoc)
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
				|| current->type == TOKEN_AND
				|| current->type == TOKEN_OR
				|| current->type == TOKEN_PIPE
				|| current->type == TOKEN_REDIR_APPEND)
			&& (current->next->type == TOKEN_AND
				|| current->next->type == TOKEN_OR
				|| current->next->type == TOKEN_PIPE))
			return (false);
		current = current->next;
	}
	return (true);
}

static void	do_tok(t_tok **new_token, char *ptr)
{
	if (ft_strcmp(ptr, "<") == 0)
		(*new_token)->type = TOKEN_REDIR_IN;
	else if (ft_strcmp(ptr, "<<") == 0)
		(*new_token)->type = TOKEN_HEREDOC;
	else if (ft_strcmp(ptr, ">") == 0)
		(*new_token)->type = TOKEN_REDIR_OUT;
	else if (ft_strcmp(ptr, ">>") == 0)
		(*new_token)->type = TOKEN_REDIR_APPEND;
	else if (ft_strcmp(ptr, "|") == 0)
		(*new_token)->type = TOKEN_PIPE;
	else if (ft_strcmp(ptr, "&&") == 0)
		(*new_token)->type = TOKEN_AND;
	else if (ft_strcmp(ptr, "||") == 0)
		(*new_token)->type = TOKEN_OR;
	else if (ft_strcmp(ptr, "(") == 0)
		(*new_token)->type = TOKEN_BRKT_OPEN;
	else if (ft_strcmp(ptr, ")") == 0)
		(*new_token)->type = TOKEN_BRKT_CLOSE;
	else if (ft_strcmp(ptr, "\"") == 0)
		(*new_token)->type = TOKEN_D_Q;
	else if (ft_strcmp(ptr, "'") == 0)
		(*new_token)->type = TOKEN_S_Q;
	else
		(*new_token)->type = TOKEN_EXPR;
}

t_tok	*syn_tokenize(char *cmdline)
{
	bool	flag;
	t_tok	*head;
	t_tok	*prev;
	char	*ptr;
	t_tok	*new_token;

	(1 == 1) && (flag = false, head = NULL, prev = NULL);
	ptr = ft_strtok(cmdline, " ", &flag);
	while (ptr)
	{
		new_token = malloc(sizeof(t_tok));
		new_token->value = ft_strdup(ptr);
		if (!new_token || !new_token->value)
			return (my_free_list(head), NULL);
		(1 == 1) && (new_token->next = NULL, new_token->prev = prev);
		if (prev != NULL)
			prev->next = new_token;
		new_token->q_flag = flag;
		do_tok(&new_token, ptr);
		if (head == NULL)
			head = new_token;
		(1 == 1) && (prev = new_token, ptr = ft_strtok(NULL, " ", &flag));
	}
	return (head);
}
