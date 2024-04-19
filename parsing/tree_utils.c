/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:44:27 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 12:21:46 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_tree(t_tree *tree, t_type type)
{
	tree->left = NULL;
	tree->right = NULL;
	tree->node_type = type;
	tree->command = NULL;
	tree->filename = NULL;
	tree->expand_heredoc = true;
	tree->content_list = NULL;
	tree->buffer = NULL;
	tree->heredoc_order = -1;
	tree->heredoc_read = false;
	tree->command_tmp = NULL;
}

t_tree	*create_tree_node(t_type type, t_config *config)
{
	t_tree	*res;

	if (config->fail)
		return (NULL);
	res = (t_tree *)malloc(sizeof(t_tree));
	if (!res)
		return (fail_config(config), NULL);
	init_tree(res, type);
	if (type == TOKEN_HEREDOC)
	{
		res->heredoc_order = config->last_heredoc + 1;
		config->last_heredoc += 1;
	}
	return (res);
}
