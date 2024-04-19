/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:34:04 by muel-bak          #+#    #+#             */
/*   Updated: 2024/04/14 16:56:03 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	if_no_args(char **args, char **env)
{
	int	i;

	if (!args || !env)
		return ;
	if (!args[1])
	{
		i = 0;
		while (env[i])
		{
			printf("declare -x %s\n", env[i]);
			i++;
		}
	}
}

char	*normalize_helper(char *value, char *leading_spaces,
			char *ending_spaces)
{
	char	**split_value;
	char	*res;

	split_value = ft_split_set(value, " \t");
	if (!split_value)
		return (NULL);
	res = join_array(split_value, true);
	res = ft_strjoin(res, ending_spaces);
	free(ending_spaces);
	ending_spaces = res;
	res = ft_strjoin(leading_spaces, res);
	free(ending_spaces);
	return (res);
}

char	*normalize_value(char *value)
{
	char	*leading_spaces;
	char	*ending_spaces;
	int		i;

	if (!value)
		return (NULL);
	i = 0;
	while (value[i] && ft_isspace(value[i]))
		i++;
	leading_spaces = ft_substr(value, 0, i);
	if (value[i])
	{
		i = ft_strlen(value) - 1;
		while (i >= 0 && ft_isspace(value[i]))
			i--;
		ending_spaces = ft_substr(value, i + 1, ft_strlen(value));
	}
	else
		ending_spaces = ft_strdup("");
	return (normalize_helper(value, leading_spaces, ending_spaces));
}

static int	export_helper(t_config *config, char *arg, char *name)
{
	char	*tmp;
	char	*value;
	char	*equal_pos;

	if (!arg)
		return (fail_config(config), 1);
	tmp = ft_strdup(arg);
	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		*equal_pos = '\0';
		name = arg;
		if (!valid_name(name, tmp))
			return (free(tmp), free(arg), 1);
		value = equal_pos + 1;
		value = normalize_value(value);
		ft_setenv(config, name, value);
	}
	if (!equal_pos && valid_name(arg, tmp))
		ft_setenv(config, arg, NULL);
	else if (!equal_pos)
		return (free(arg), free(tmp), 1);
	free(arg);
	free(tmp);
	return (0);
}

int	ft_export(t_config *config, char **args)
{
	char	**env;
	char	*name;
	int		i;

	name = NULL;
	env = config->env;
	if_no_args(args, env);
	i = 1;
	while (args[i] && !config->fail)
	{
		if (export_helper(config, ft_strdup(args[i]), name))
			return (1);
		i++;
	}
	return (0);
}
