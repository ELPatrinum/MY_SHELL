/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:15:03 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 12:47:35 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**append_command(char **commands, char *command, t_config *config)
{
	char	**res;
	int		i;

	i = 0;
	if (!command)
		return (NULL);
	if (!(ft_strlen(command) || config->content_quoted))
		return (free(command), commands);
	while (commands && commands[i])
		i++;
	res = (char **) malloc(sizeof(char *) * (i + 2));
	if (!res)
		return (free_array(commands), free(command), NULL);
	i = 0;
	while (commands && commands[i])
	{
		res[i] = commands[i];
		i++;
	}
	res[i] = command;
	i++;
	res[i] = NULL;
	free(commands);
	return (res);
}

char	*append_special(char **split_word)
{
	char	*res;
	int		i;

	if (!split_word)
		return (NULL);
	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (split_word[i])
	{
		if (split_word[i + 1])
			split_word[i] = append_char(split_word[i], 7);
		res = ft_strjoin(res, split_word[i]);
		if (!res)
			return (NULL);
		i++;
	}
	return (res);
}

char	*append_char(char *str, char c)
{
	char	*tmp;
	char	*res;

	tmp = (char *)malloc(sizeof(char) * 2);
	if (!tmp)
		return (free(str), NULL);
	tmp[0] = c;
	tmp[1] = 0;
	res = ft_strjoin(str, tmp);
	free(tmp);
	return (res);
}
