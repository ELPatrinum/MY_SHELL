/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:32:52 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/19 11:18:34 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_variable(char *variable)
{
	char	**res;
	int		i;

	i = 0;
	if (!variable)
		return (NULL);
	res = (char **) malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	while (variable[i] && variable[i] != '=')
		i++;
	if (!variable[i])
		return (free(res), NULL);
	res[0] = ft_substr(variable, 0, i);
	if (!res[0])
		return (free(res), NULL);
	i++;
	if (!variable[i])
		res[1] = ft_strdup("");
	else
		res[1] = ft_substr(variable, i, ft_strlen(variable));
	if (!res[1])
		return (free(res[0]), free(res), NULL);
	return (res);
}

void	append_env_node(t_env **list, char *variable)
{
	t_env	*node;
	t_env	*tmp;
	char	**split_var;

	if (!list || !variable)
		return ;
	node = (t_env *) malloc(sizeof(t_env));
	if (!node)
		return (free_list_null(list));
	split_var = split_variable(variable);
	if (split_var)
		(1 == 1) && (node->name = split_var[0], node->value = split_var[1]);
	else
		(1 == 1) && (node->name = ft_strdup(variable), node->value = NULL);
	(1 == 1) && (node->full = ft_strdup(variable), node->next = NULL);
	free(split_var);
	if (!(*list))
	{
		*list = node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_env	*get_env_list(t_config *config)
{
	t_env	*list;
	char	**env;
	int		i;

	if (config->env_list)
		free_env_list(config->env_list);
	env = config->env;
	if (!env)
		return (NULL);
	list = NULL;
	i = 0;
	while (env[i])
	{
		append_env_node(&list, env[i]);
		if (!list)
			return (fail_config(config), NULL);
		i++;
	}
	return (list);
}

char	*ft_getenv(char **env, const char *name)
{
	int	i;

	if (!env || !name)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
			return (env[i] + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}

char	**list_to_array(t_env *env)
{
	t_env	*tmp;
	char	**res;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (!i)
		return (NULL);
	res = (char **) malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (env)
	{
		res[i] = ft_strdup(env->full);
		env = env->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
