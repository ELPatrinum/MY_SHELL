/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:54:46 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/17 09:42:23 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_only_spaces(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	read_execute(t_config *config, char **line)
{
	if (is_only_spaces(*line))
		return ;
	if (g_here_flag[1])
		config->last_status = 1;
	check_line(config, *line);
	config->tmp_line = ft_strdup(*line);
	check_break(config, 1);
	if (!check_syn((char *)(*line))
	|| !ft_syntax(*line, &(config->heredocs_to_execute), &(config->error_msg)))
		handle_syntax_error(config);
	check_break(config, 2);
	if (!ft_strlen(config->tmp_line) && free_null(&(config->tmp_line)))
		return ;
	if (set_lex(config) && !config->tmp_list && display_free(config))
		return ;
	config->tokens_list = (config->tmp_list);
	if ((parse_init(config) && (!config->tmp_tree || config->fail)
			&& parse_fail(config))
		|| !execute(config))
		return ;
}

int	main(int argc, char *argv[], char *env[])
{
	t_config	config;
	char		*line;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	ft_void(argc, argv);
	init_config(&config, env);
	while (true)
	{
		reset_config(&config);
		line = readline("\033[0;35mELPatrinum\n$> \033[0;37m");
		config.tmp = line;
		if (line)
		{
			add_history(line);
			config.std_in = dup(STDIN_FILENO);
			config.std_out = dup(STDOUT_FILENO);
		}
		read_execute(&config, &line);
		finish_execution(&config);
	}
	return(free_garbage(&config), free_array(config.env), 0);
}
