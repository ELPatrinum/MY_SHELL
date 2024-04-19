/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:01:19 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 16:56:37 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_env(t_config *config)
{
	char	*tmp;
	int		shell_level;

	if (!ft_getenv(config->env, "PATH"))
		ft_setenv(config, "PATH",
			ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	if (!ft_getenv(config->env, "SHLVL"))
		ft_setenv(config, "SHLVL", ft_strdup("1"));
	else
	{
		tmp = ft_getenv(config->env, "SHLVL");
		shell_level = ft_atoi(tmp) + 1;
		tmp = ft_itoa(shell_level);
		ft_setenv(config, "SHLVL", tmp);
	}
	if (!ft_getenv(config->env, "_"))
		ft_setenv(config, "_", ft_strdup("/usr/bin/env"));
	if (!ft_getenv(config->env, "PWD"))
	{
		tmp = NULL;
		tmp = getcwd(tmp, 0);
		ft_setenv(config, "PWD", tmp);
	}
	update_env(config);
}

void	init_config(t_config *config, char **env)
{
	config->env = env;
	config->fail = false;
	config->last_status = 0;
	config->env_exists = true;
	if (!env || !env[0])
		config->env_exists = false;
	config->i = 0;
	config->env = allocate_environment(env);
	config->env_list = NULL;
	config->env_list = get_env_list(config);
	if (config->fail)
	{
		free_garbage(config);
		free_array(config->env);
		exit(0);
	}
	rl_catch_signals = 0;
	config->error_msg = NULL;
	check_env(config);
	if (config->fail)
	{
		free_garbage(config);
		free_array(config->env);
		exit(0);
	}
}

void	reset_config(t_config *config)
{
	config->flag = 0;
	config->tmp = NULL;
	config->heredocs_to_execute = 0;
	config->last_heredoc = -1;
	config->heredocs_executed = 0;
	config->fail = false;
	config->content_quoted = false;
	config->tmp_tree = NULL;
	config->tmp_line = NULL;
	config->tmp_list = NULL;
	config->error_msg = NULL;
	g_here_flag[0] = 0;
	g_here_flag[1] = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_int);
	config->std_in = -1;
	config->std_out = -1;
	config->tmp_line = NULL;
}

int	free_null(char **str)
{
	free(*str);
	*str = NULL;
	return (1);
}

void	print_error(t_config *config)
{
	put_error(config->error_msg, "", "");
	free(config->error_msg);
	config->error_msg = NULL;
}
