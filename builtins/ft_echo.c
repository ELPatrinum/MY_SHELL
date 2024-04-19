/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:10:42 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/19 19:49:31 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	opt(char *str, int *i, int *j, bool *option)
{
	while (str[*i] && str[*i] == '-' && str[(*i) + 1] == 'n')
	{
		*j = *i;
		(*i)++;
		while (str[*i] && str[*i] == 'n')
			(*i)++;
		if (str[*i] && str[*i] == ' ')
			*option = true ;
		else
		{
			*i = *j;
			break ;
		}
		while (str[*i] && str[*i] == ' ')
			(*i)++;
	}
}

static	bool	echo_helper(char *str, int *i)
{
	if (str[*i] && str[*i] == '-' && str[(*i) + 1] == 'n')
	{
		(*i)++;
		while ((str[*i] && str[*i] == 'n') || (str[*i] && ft_isspace(str[*i])))
			(*i)++;
		if (!str[*i])
			return (false);
	}
	return (true);
}

int	ft_echo(char *str)
{
	int		i;
	int		j;
	int		x;
	bool	option;

	i = 0;
	j = 0;
	option = false;
	if (!str)
		return (1);
	opt(str, &i, &j, &option);
	if (!option)
		i = j;
	x = i;
	if (!echo_helper(str, &i))
		return (0);
	if (str[i] && !ft_isspace(str[i]))
		i = x;
	ft_putstr_fd(str + i, 1);
	if (option)
		return (0);
	ft_putstr_fd("\n", 1);
	return (0);
}
