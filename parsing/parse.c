/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:43:20 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 11:35:05 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*parse_cmdline(t_config *config)
{
	t_lex	**tokens_list;
	t_tree	*res;
	t_type	token;

	tokens_list = &(config->tokens_list);
	if (!tokens_list || !(*tokens_list) || config->fail)
		return (NULL);
	res = parse_pipe(config);
	if (config->fail)
		return (free_tree(res), NULL);
	if ((*tokens_list) && ((*tokens_list)->node_type == TOKEN_AND
			|| (*tokens_list)->node_type == TOKEN_OR))
	{
		token = (*tokens_list)->node_type;
		*tokens_list = (*tokens_list)->next;
		res = construct_cmdline(res, parse_cmdline(config), token, config);
		if (config->fail)
			return (NULL);
	}
	return (res);
}

t_tree	*parse_pipe(t_config *config)
{
	t_lex	**tokens_list;
	t_tree	*res;

	tokens_list = &(config->tokens_list);
	if (!tokens_list || !(*tokens_list) || config->fail)
		return (NULL);
	res = parse_command(config);
	if (config->fail)
		return (free_tree(res), NULL);
	while ((*tokens_list) && is_redirection((*tokens_list)->node_type))
		res = parse_redir(config, res);
	if ((*tokens_list) && ((*tokens_list)->node_type == TOKEN_PIPE))
	{
		*tokens_list = (*tokens_list)->next;
		res = construct_pipe(res, parse_pipe(config), config);
		if (config->fail)
			return (NULL);
	}
	return (res);
}

t_tree	*parse_command(t_config *config)
{
	t_lex	**tokens_list;
	t_tree	*res;

	tokens_list = &(config->tokens_list);
	if (!tokens_list || !(*tokens_list) || config->fail)
		return (NULL);
	res = parse_cmdlist(config);
	if (config->fail)
		return (free_tree(res), NULL);
	if ((*tokens_list) && (*tokens_list)->node_type == TOKEN_BRKT_OPEN)
	{
		*tokens_list = (*tokens_list)->next;
		res = construct_command(parse_cmdline(config), res, config);
		if (*tokens_list)
			*tokens_list = (*tokens_list)->next;
		if (config->fail)
			return (NULL);
	}
	return (res);
}

t_tree	*parse_pre_redirs(t_config *config)
{
	t_tree	*res;

	res = NULL;
	while ((config->tokens_list)
		&& is_redirection(((config->tokens_list))->node_type))
	{
		res = parse_redir(config, res);
		if (config->fail)
			return (NULL);
	}
	return (res);
}

t_tree	*parse_cmdlist(t_config *config)
{
	t_tree	*res;
	t_tree	*tmp;

	if (check_fail(&(config->tokens_list), config)
		|| (((config->tokens_list))->node_type == TOKEN_BRKT_OPEN))
		return (NULL);
	res = parse_pre_redirs(config);
	if (res)
	{
		tmp = res;
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = parse_exec(config);
	}
	else
		res = parse_exec(config);
	if (config->fail)
		return (free_tree(res), NULL);
	while (!config->fail && (config->tokens_list)
		&& is_redirection(((config->tokens_list))->node_type))
		res = parse_redir(config, res);
	if (config->fail)
		return (NULL);
	return (res);
}
