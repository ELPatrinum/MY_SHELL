/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:57:21 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/12 11:26:24 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_reset(t_config *config)
{
	int	status;

	close(config->std_in);
	close(config->std_out);
	config->std_in = dup(STDIN_FILENO);
	config->std_out = dup(STDOUT_FILENO);
	execute_redir(config);
	if (config->fail)
		return (1);
	status = execute_cmdline(config);
	dup2(config->std_out, STDOUT_FILENO);
	dup2(config->std_in, STDIN_FILENO);
	close(config->std_in);
	close(config->std_out);
	return (status);
}
