/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:35:18 by muel-bak          #+#    #+#             */
/*   Updated: 2024/04/14 16:55:58 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_config *config, char **args)
{
	int		i;
	t_env	*env;

	env = config->env_list;
	if (!args || !env)
		return (1);
	if (!args[1])
		return (0);
	else
	{
		i = 1;
		while (args[i])
		{
			if (!valid_name_unset(args[i]))
				return (1);
			ft_unsetenv(config, args[i]);
			i++;
		}
	}
	return (0);
}
