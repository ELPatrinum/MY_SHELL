/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:17:07 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 16:56:27 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**handle_star(char **res, int *i, char op)
{
	char	*tmp;
	char	**words;
	int		count;

	tmp = expand_star(res[*i], &count);
	free(res[*i]);
	res[*i] = tmp;
	if (op == 'f' && count > 1)
		return (free_array(res), NULL);
	words = ft_split(res[*i], 7);
	if (!words)
		return (free_array(res), NULL);
	if (count == 1)
	{
		free(res[*i]);
		res[*i] = words[0];
		free(words);
	}
	else if (count > 1)
		res = insert_array(res, words, i);
	else
		free_array(words);
	return (res);
}

char	**finish_command(char **res, char op)
{
	char	**words;
	int		i;

	i = 0;
	while (res && res[i])
	{
		if (ft_strchr(res[i], 7))
		{
			words = ft_split(res[i], 7);
			res = insert_array(res, words, &i);
		}
		if (res && res[i] && ft_strchr(res[i], '*'))
		{
			res = handle_star(res, &i, op);
		}
		if (res && res[i] && ft_strchr(res[i], 6))
			res[i] = remove_char(res[i], 6);
		i++;
	}
	return (res);
}

char	**handle_finish(t_config *config, char **res, char op)
{
	if (!res)
		return (fail_config(config), NULL);
	return (finish_command(res, op));
}

static char	*get_tmp(t_config *config, t_content *content_list)
{
	return (expand_variables(ft_strdup(content_list->str), config,
			content_list->node_type == TOKEN_D_Q,
			check_next_quoted(content_list)));
}

char	*get_normal_command(t_content *content_list,
t_config *config, char *command, char op)
{
	char	**words;
	char	*tmp;

	if (content_list->node_type == TOKEN_D_Q)
		config->content_quoted = true;
	if (op == 'f')
	{
		tmp = get_tmp(config, content_list);
		words = ft_split(tmp, 7);
		free(tmp);
		if (!words)
			return (fail_config(config), free(command), NULL);
		if (words && words[0] && words[1])
			return (free_array(words), free(command), NULL);
		command = ft_strjoin(command, words[0]);
		free_array(words);
	}
	else
	{
		tmp = get_tmp(config, content_list);
		if (ft_strlen(tmp) || content_list->node_type == TOKEN_D_Q)
			command = ft_strjoin(command, tmp);
		free(tmp);
	}
	return (command);
}
