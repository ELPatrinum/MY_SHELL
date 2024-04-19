/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:58:02 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/11 20:10:49 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_subshell(t_config *config, t_tree *tree)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit(0);
	if (!pid)
	{
		config->tree = (tree)->left;
		status = execute_cmdline(config);
		exit(status);
	}
	wait(&status);
	return (WEXITSTATUS(status));
}
