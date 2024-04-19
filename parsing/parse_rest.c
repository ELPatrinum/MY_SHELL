/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:42:22 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 12:19:57 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_tree	*get_last_node(t_tree *tree)
{
	while (tree && tree->left)
		tree = tree->left;
	return (tree);
}

static void	check_args_redir(t_config *config,
t_tree *last, t_lex **tokens_list)
{
	t_content	*tmp;

	if ((*tokens_list) && is_executable(*tokens_list))
	{
		append_content_node(&last->content_list, NULL, -1);
		tmp = last->content_list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = get_content_list(config, 'c');
	}
}

t_tree	*parse_redir(t_config *config, t_tree *tree)
{
	t_lex	**tokens_list;
	t_tree	*res;
	t_tree	*last;

	tokens_list = &(config->tokens_list);
	if (!(*tokens_list) || config->fail)
	{
		free_tree(tree);
		return (NULL);
	}
	res = construct_redir((*tokens_list)->node_type,
			tokens_list, tree, config);
	if (config->fail)
	{
		free_tree(tree);
		return (NULL);
	}
	last = get_last_node(tree);
	if (!last || is_redirection(last->node_type))
		return (res);
	check_args_redir(config, last, tokens_list);
	return (res);
}

t_tree	*parse_exec(t_config *config)
{
	t_lex	**tokens_list;
	t_tree	*res;

	res = NULL;
	tokens_list = &(config->tokens_list);
	if (!(*tokens_list) || config->fail
		|| !(((*tokens_list))->node_type == TOKEN_EXEC
			|| ((*tokens_list))->node_type == TOKEN_D_Q
			|| ((*tokens_list))->node_type == TOKEN_S_Q))
		return (NULL);
	res = create_tree_node((*tokens_list)->node_type, config);
	if (!res)
		return (NULL);
	res->content_list = get_content_list(config, 'c');
	if (!res->content_list)
	{
		config->fail = true;
		return (free_tree(res), NULL);
	}
	return (res);
}
