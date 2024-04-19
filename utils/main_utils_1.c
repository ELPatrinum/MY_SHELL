/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:41:21 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 16:56:31 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_syntax_error(t_config *config)
{
	if (!(config->heredocs_to_execute))
	{
		ft_free(config->tmp_line);
		config->tmp_line = ft_strdup("\n");
	}
	config->last_status = 258;
	config->flag = 1;
}

void	check_break(t_config *config, int op)
{
	if ((op == 2 || op == 1) && !(config->tmp_line))
	{
		free_garbage(config);
		free_array(config->env);
		exit(0);
	}
}

void	check_line(t_config *config, char *line)
{
	int	tmp;

	if (!line && write(1, "exit\n", 5))
	{
		tmp = config->last_status;
		free_garbage(config);
		free_array(config->env);
		exit(tmp);
	}
}

void	ft_void(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	set_lex(t_config *config)
{
	config->line = config->tmp_line;
	config->tmp_list = lex_line(&(config->line));
	return (1);
}
