/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:01:21 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/19 21:00:36 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	valid_name(char *name, char *full)
{
	int	x;

	x = 0;
	while (name[x] != '\0' && name[x] != '=')
	{
		if ((name[x] >= 33 && name[x] <= 42)
			|| (name[x] >= 44 && name[x] <= 47)
			|| (name[x] == '+' && name[x + 1] != '\0'))
		{
			put_error("minishell: export: ",
				full, ": not a valid identifier\n");
			return (false);
		}
		x++;
	}
	if (!ft_strlen(name) || (name[0] >= '0' && name[0] <= '9'))
	{
		put_error("minishell: export: ",
			full, ": not a valid identifier\n");
		return (false);
	}
	return (true);
}

bool	valid_name_unset(char *name)
{
	int	x;

	x = 0;
	while (name[x] != '\0')
	{
		if ((name[x] >= 33 && name[x] <= 42)
			|| (name[x] >= 44 && name[x] <= 47)
			|| (name[x] == '+' || name[x] == '='))
		{
			put_error("minishell: unset: ",
				name, ": not a valid identifier\n");
			return (false);
		}
		x++;
	}
	if (!ft_strlen(name) || (name[0] >= '0' && name[0] <= '9'))
	{
		put_error("minishell: unset: ", name, ": not a valid identifier\n");
		return (false);
	}
	return (true);
}
