/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:49:20 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 11:30:14 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_issymbol(char c)
{
	return (!ft_isalpha(c) && !ft_strchr("#_!@", c));
}

char	*check_and_join(char *word, int *count, DIR *dir)
{
	struct dirent	*ent;
	char			*res;

	ent = readdir(dir);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (ent)
	{
		if (check_match(word, ent->d_name)
			&& (word[0] == '.' || (word[0] != '.'
					&& ent->d_name[0] != '.')))
		{
			(*count)++;
			res = ft_strjoin(res, "\007");
			res = ft_strjoin(res, ent->d_name);
			if (!res)
				return (NULL);
		}
		ent = readdir(dir);
	}
	return (res);
}

bool	is_only_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (false);
		i++;
	}
	return (true);
}

char	*get_env_var(char *name, t_config *config)
{
	char	*res;

	res = ft_getenv(config->env, name);
	if (!res)
		res = "";
	free(name);
	return (res);
}
