/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:40:08 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 13:42:49 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_cmdline(t_config *config)
{
	t_tree	*tree;
	int		status;

	signal(SIGQUIT, &sig_int);
	tree = config->tree;
	if (!tree)
		return (0);
	if ((((tree)->node_type >= 2 && (tree)->node_type <= 5)))
		return (redirect_reset(config));
	else if ((tree)->node_type == TOKEN_AND
		|| (tree)->node_type == TOKEN_OR)
		return (execute_condition(config));
	else if ((tree)->node_type == TOKEN_PIPE)
		return (execute_pipe(config));
	else if ((tree)->node_type == TOKEN_EXEC
		|| (tree)->node_type == TOKEN_D_Q
		|| (tree)->node_type == TOKEN_S_Q)
		return (execute_single(config));
	else if ((tree)->node_type == TOKEN_EXPR)
		return (execute_subshell(config, tree));
	while (wait(&status) > 0)
		signal(SIGINT, &handleint);
	return (WEXITSTATUS(status));
}
