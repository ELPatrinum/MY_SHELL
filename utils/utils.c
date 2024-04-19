/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:41:03 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 20:11:23 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	init_vars(char ***split_paths, char **tmp, char *paths, int *i)
{
	*split_paths = NULL;
	*i = 0;
	*tmp = NULL;
	*split_paths = ft_split(paths, ':');
	if (!(*split_paths))
		return (0);
	return (1);
}

char	*find_path(char *command, char *paths)
{
	char	**split_paths;
	char	*tmp;
	int		i;

	if (!paths || !command)
		return (NULL);
	if (!ft_strlen(command) || ft_strchr("./", command[0]))
		return (ft_strdup(command));
	if (!init_vars(&split_paths, &tmp, paths, &i))
		return (NULL);
	while (split_paths[i])
	{
		tmp = ft_strjoin(ft_strdup(split_paths[i]), "/");
		if (!tmp)
			return (free_array(split_paths), NULL);
		tmp = ft_strjoin(tmp, command);
		if (!tmp)
			return (free_array(split_paths), NULL);
		if (!access(tmp, F_OK))
			return (free_array(split_paths), tmp);
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (free_array(split_paths), free(tmp), ft_strdup(command));
}

char	*join_array(char **arr, bool free_arr)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (arr[i])
	{
		if (i > 0)
			res = ft_strjoin(res, " ");
		res = ft_strjoin(res, arr[i]);
		i++;
	}
	if (free_arr)
		free_array(arr);
	return (res);
}

char	*guard_command(char *command, t_content *content_list)
{
	command = ft_strjoin(command, "\006");
	command = ft_strjoin(command, content_list->str);
	command = ft_strjoin(command, "\006");
	return (command);
}

char	*trim_free(char *str)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = str;
	str = ft_strtrim(str, " \t");
	free(tmp);
	return (str);
}
