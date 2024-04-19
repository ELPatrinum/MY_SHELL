/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:41:14 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 11:40:44 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*construct_cmdline(t_tree *left,
t_tree *right, t_type type, t_config *config)
{
	t_tree	*res;

	if (config->fail)
		return (free_tree(left), free_tree(right), NULL);
	res = create_tree_node(type, config);
	if (!res)
		return (free_tree(left), free_tree(right), fail_config(config), NULL);
	if (right && (right->node_type == TOKEN_OR
			|| right->node_type == TOKEN_AND))
	{
		res->right = right->left;
		res->left = left;
		right->left = res;
		return (right);
	}
	else
	{
		res->left = left;
		res->right = right;
	}
	return (res);
}

t_tree	*construct_pipe(t_tree *left, t_tree *right, t_config *config)
{
	t_tree	*res;

	if (config->fail)
		return (free_tree(left), free_tree(right), NULL);
	res = create_tree_node(TOKEN_PIPE, config);
	if (!res)
		return (free_tree(left), free_tree(right), fail_config(config), NULL);
	res->left = left;
	res->right = right;
	return (res);
}

t_tree	*construct_command(t_tree *left, t_tree *right, t_config *config)
{
	t_tree	*res;

	if (config->fail)
		return (free_tree(left), free_tree(right), NULL);
	res = create_tree_node(TOKEN_EXPR, config);
	if (!res)
		return (free_tree(left), free_tree(right), fail_config(config), NULL);
	res->left = left;
	res->right = right;
	return (res);
}

void	set_heredoc_expand(t_tree *tree)
{
	t_content	*tmp_content;

	tmp_content = tree->content_list;
	while (tmp_content)
	{
		if (tmp_content->node_type == TOKEN_D_Q
			|| tmp_content->node_type == TOKEN_S_Q)
		{
			tree->expand_heredoc = false;
			break ;
		}
		tmp_content = tmp_content->next;
	}
}

t_tree	*construct_redir(int token, t_lex **tokens_list,
t_tree *tree, t_config *config)
{
	t_tree		*res;
	t_tree		*tmp;

	if (!tokens_list || !(*tokens_list) || config->fail)
		return (free_tree(tree), NULL);
	res = create_tree_node(token, config);
	if (!res)
		return (free_tree(tree), fail_config(config), NULL);
	*tokens_list = (*tokens_list)->next;
	res->content_list = get_content_list(config, 'f');
	if (!res->content_list)
		return (free(res), tree);
	set_heredoc_expand(res);
	if (tree && is_redirection(tree->node_type))
	{
		tmp = tree;
		while (tmp && tmp->left && is_redirection(tmp->left->node_type))
			tmp = tmp->left;
		res->left = tmp->left;
		tmp->left = res;
		return (tree);
	}
	else
		res->left = tree;
	return (res);
}
