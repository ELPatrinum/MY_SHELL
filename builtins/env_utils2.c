/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:10:18 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/19 20:13:25 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_env_value(t_env **env, const char *name, char *value)
{
	char	*variable;

	if (*env)
	{
		if (ft_strlen(name) == ft_strlen((*env)->name)
			&& !ft_strncmp(name, (*env)->name, ft_strlen(name)))
		{
			if (!value)
				return (1);
			free((*env)->value);
			free((*env)->full);
			value = trim_free(value);
			(*env)->value = ft_strdup(value);
			variable = ft_strdup("");
			variable = ft_strjoin(variable, name);
			variable = ft_strjoin(variable, "=");
			variable = ft_strjoin(variable, value);
			(*env)->full = variable;
			free(value);
			return (1);
		}
		else
			return (update_env_value(&((*env)->next), name, value));
	}
	return (0);
}

void	append_value(t_config *config, char *name, char *value)
{
	char	*old_value;
	char	*new_value;
	char	*tmp;

	if (!name || !value)
		return (free(value));
	tmp = ft_strchr(name, '+');
	if (tmp && (tmp + 1) && *(tmp + 1))
		return ;
	tmp = ft_substr(name, 0, ft_strlen(name) - 1);
	if (!tmp)
		return (fail_config(config), free(value));
	old_value = ft_strdup(get_env_var(ft_strdup(tmp), config));
	new_value = ft_strjoin(old_value, value);
	free(value);
	if (!new_value)
		return (fail_config(config), free(tmp));
	ft_setenv(config, tmp, new_value);
	free(tmp);
	return ;
}

void	ft_setenv(t_config *config, char *name, char *value)
{
	char	*variable;

	if (!name || config->fail)
		return ;
	if (ft_strchr(name, '+'))
		return (append_value(config, name, value));
	if (update_env_value(&(config->env_list), name, value) == 1)
		return ;
	if (config->fail)
		return ;
	variable = ft_strdup("");
	variable = ft_strjoin(variable, name);
	value = trim_free(value);
	if (value)
	{
		variable = ft_strjoin(variable, "=");
		variable = ft_strjoin(variable, value);
		free(value);
	}
	if (!variable)
		return (fail_config(config));
	append_env_node(&(config->env_list), variable);
	free(variable);
}

void	remove_env_node(t_env **head, const char *name)
{
	t_env	*env;
	t_env	*prev;

	env = *head;
	prev = NULL;
	while (env)
	{
		if (ft_strlen(name) == ft_strlen(env->name)
			&& !ft_strncmp(name, env->name, ft_strlen(name)))
		{
			if (prev)
				prev->next = env->next;
			else
				*head = env->next;
			free(env->full);
			free(env->name);
			free(env->value);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

void	ft_unsetenv(t_config *config, const char *name)
{
	if (!(config->env_list) || !name)
		return ;
	remove_env_node(&(config->env_list), name);
}
