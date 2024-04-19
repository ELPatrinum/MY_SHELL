/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_condition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:59:53 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/11 20:11:31 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	execute_condition_and(t_config *config, t_tree *tree)
{
	int		status;
	t_tree	*tmp;

	tmp = (tree)->right;
	config->tree = tree->left;
	status = execute_cmdline(config);
	wait(NULL);
	if (status != EXIT_SUCCESS)
		return (status);
	config->tree = tmp;
	status = execute_cmdline(config);
	return (status);
}

static int	execute_condition_or(t_config *config, t_tree *tree)
{
	int		status;
	t_tree	*tmp;

	tmp = (tree)->right;
	config->tree = (tree)->left;
	status = execute_cmdline(config);
	if (status == EXIT_SUCCESS)
		return (status);
	config->tree = tmp;
	status = execute_cmdline(config);
	return (status);
}

int	execute_condition(t_config *config)
{
	t_tree	*tree;

	tree = config->tree;
	if (!tree)
		return (0);
	if ((tree)->node_type == TOKEN_AND)
		return (execute_condition_and(config, tree));
	else
		return (execute_condition_or(config, tree));
}
