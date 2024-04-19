/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:21:12 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 11:43:46 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_config *config)
{
	char	**new_env;

	if (config->fail)
		return ;
	new_env = list_to_array(config->env_list);
	if (!new_env)
		return ;
	free_array(config->env);
	config->env = new_env;
}

void	fail_config(t_config *config)
{
	config->fail = true;
	return ;
}

void	put_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}
