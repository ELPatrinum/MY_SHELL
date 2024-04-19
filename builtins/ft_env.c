/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:36:13 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/15 14:54:41 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **env, t_config *config)
{
	int		i;
	char	*c;

	if (!env)
		return (0);
	i = 0;
	if (!config->env_exists && !ft_strncmp(env[0], "PATH", 4))
		i = 1;
	while (env[i])
	{
		c = ft_strchr(env[i], '=');
		if (!c || !*c)
		{
			i++;
			continue ;
		}
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
