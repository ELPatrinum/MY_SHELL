/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:55:01 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 16:50:09 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_all(t_config *config)
{
	free_garbage(config);
	free_array(config->env);
}

static int	execute_builtin_rest(t_config *config, char **args)
{
	int			status;
	char		*cwd;
	static bool	cd_flag = false;

	cwd = NULL;
	status = 0;
	if (!ft_strncmp(args[0], "unset", ft_strlen(args[0])))
	{
		status = ft_unset(config, args);
		update_env(config);
	}
	else if (!ft_strncmp(args[0], "pwd", ft_strlen(args[0])))
		status = ft_pwd(config);
	else if (!ft_strncmp(args[0], "env", ft_strlen(args[0])))
		status = ft_env(config->env, config);
	else if (!ft_strncmp(args[0], "cd", ft_strlen(args[0])))
	{
		status = ft_cd(args[1], (config)->env, &cd_flag);
		cwd = getcwd(cwd, 0);
		if (status == 3 && !cwd)
			return (ft_update_faile(&(config)->env, args[1]), 1);
		else
			ft_update(&(config)->env);
	}
	return (free(cwd), status);
}

static bool	is_digits(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr("-+", str[0]))
		i = 1;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (!str[i] && ((ft_strchr("-+", str[0])
				&& ft_strlen(str) > 1) || ft_strlen(str)))
		return (true);
	return (false);
}

int	ft_exit(char **args, t_config *config)
{
	int	number;

	if ((args[1] && !is_digits(args[1])) || ft_strlen(args[1]) > 19)
	{
		put_error("exit\nminishell: exit: ", args[1],
			": numeric argument required\n");
		free_all(config);
		exit(255);
	}
	if (args[1] && args[2])
	{
		put_error("exit\n", "minishell: exit: too many arguments\n", "");
		return (1);
	}
	printf("exit\n");
	number = config->last_status;
	if (args[1])
		number = ft_atoi(args[1]);
	free_all(config);
	if (number > 255 || number < 0)
		exit(number % 256);
	exit(number);
}

int	execute_builtin(t_config *config)
{
	char	**args;
	char	*tmp;
	int		status;

	args = ((config->tree))->command;
	if (!args || !args[0])
		return (0);
	if (!ft_strncmp(args[0], "exit", ft_strlen(args[0])))
		status = ft_exit(args, config);
	else if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
	{
		tmp = join_array(&args[1], false);
		status = ft_echo(tmp);
		free(tmp);
	}
	else if (!ft_strncmp(args[0], "export", ft_strlen(args[0])))
	{
		status = ft_export(config, args);
		update_env(config);
	}
	else
		status = execute_builtin_rest(config, args);
	return (status);
}
