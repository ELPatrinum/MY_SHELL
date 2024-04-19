/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:40:44 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 11:48:08 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	display_free(t_config *config)
{
	if (config->flag && config->error_msg)
		print_error(config);
	free_null(&(config->tmp_line));
	return (1);
}

void	finish_execution(t_config *config)
{
	if (config->std_in != -1)
	{
		dup2(config->std_in, STDIN_FILENO);
		dup2(config->std_out, STDOUT_FILENO);
	}
	free_garbage(config);
}

int	parse_init(t_config *config)
{
	config->env_list = get_env_list(config);
	if (config->fail)
		return (0);
	config->tmp_tree = parse_cmdline(config);
	return (1);
}

int	parse_fail(t_config *config)
{
	if (config->flag && config->error_msg)
		print_error(config);
	free_garbage(config);
	return (1);
}

int	execute(t_config *config)
{
	traverse_heredoc(config->tmp_tree, config, 0);
	if (config->error_msg)
		print_error(config);
	if (config->fail || g_here_flag[0] || config->flag)
	{
		if (g_here_flag[0] || config->heredocs_to_execute > 0)
			config->last_status = 1;
		free_garbage(config);
		return (0);
	}
	config->tree = config->tmp_tree;
	config->last_status = execute_cmdline(config);
	return (1);
}
