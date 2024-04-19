/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:19:23 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 19:47:18 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_full_size(char **first, char **second)
{
	int	i;
	int	size;

	size = 0;
	i = -1;
	while (first[++i])
		;
	size = i;
	i = -1;
	while (second[++i])
		;
	size += i;
	return (size);
}

static int	copy_first(char ***res, char **first, int *i, int *j)
{
	*j = 0;
	while (*j < (*i))
	{
		(*res)[*j] = ft_strdup(first[*j]);
		if (!((*res)[*j]))
		{
			free_array(*res);
			*res = NULL;
			return (0);
		}
		(*j)++;
	}
	return (1);
}

static int	copy_second(char ***res, char **second, int *k, int *j)
{
	*k = 0;
	while (second[*k])
	{
		(*res)[*j] = ft_strtrim(second[*k], "\007");
		if (!((*res)[*j]))
		{
			free_array(*res);
			*res = NULL;
			return (0);
		}
		(*k)++;
		(*j)++;
	}
	return (1);
}

static int	finish_first(char ***res, char **first, int *k, int *j)
{
	while (first[*k])
	{
		(*res)[*j] = ft_strdup(first[*k]);
		if (!((*res)[*j]))
		{
			free_array(*res);
			*res = NULL;
			return (0);
		}
		(*k)++;
		(*j)++;
	}
	return (1);
}

char	**insert_array(char **first, char **second, int *i)
{
	size_t	size;
	int		j;
	int		k;
	char	**res;

	if (!first || !second)
		return (first);
	size = get_full_size(first, second);
	res = (char **) malloc(sizeof(char *) * (size));
	if (!res)
		return (free_array(first), free_array(second), NULL);
	if (!copy_first(&res, first, i, &j))
		return (free_array(first), free_array(second), NULL);
	if (!copy_second(&res, second, &k, &j))
		return (free_array(first), free_array(second), NULL);
	k = *i + 1;
	if (!finish_first(&res, first, &k, &j))
		return (free_array(first), free_array(second), NULL);
	res[j] = NULL;
	free_array(first);
	free_array(second);
	return (res);
}
