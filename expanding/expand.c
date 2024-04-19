/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:59:04 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 11:23:02 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*set_tmp(char *word, int *i, t_config *config)
{
	char	*expand_tmp;
	char	*tmp;

	if (!word || config->fail)
		return (NULL);
	while (word[(*i)])
	{
		if (ft_issymbol(word[(*i)]))
			break ;
		(*i)++;
	}
	tmp = ft_substr(word, 0, (*i));
	if (!tmp)
		return (fail_config(config), NULL);
	if (ft_isspace(word[0]))
	{
		expand_tmp = tmp;
		tmp = ft_strjoin(ft_strdup("$"), tmp);
		free(expand_tmp);
		if (!tmp)
			return (fail_config(config), NULL);
	}
	else
		tmp = ft_strdup(get_env_var(tmp, config));
	return (tmp);
}

char	*get_variable_value(t_config *config,
char *word, int i, bool next_quoted)
{
	char	*tmp;
	char	*expand_tmp;

	if (ft_strchr("*", word[i]) || ft_isdigit(word[i]))
		return (expand_special(config, word, next_quoted));
	else if (word[i] == '?' || ft_strchr(".=", word[i]))
		return (expand_point_exit(config, word, i, next_quoted));
	else
	{
		tmp = set_tmp(word, &i, config);
		if (!tmp)
			return (free(word), fail_config(config), NULL);
		if (!word[i])
			return (free(word), tmp);
		if (ft_issymbol(word[i]))
		{
			expand_tmp = expand_word(ft_strdup(word + i), 0,
					config, next_quoted);
			tmp = ft_strjoin(tmp, expand_tmp);
			if (!expand_tmp)
				return (free(expand_tmp), free(word), fail_config(config), tmp);
			return (free(expand_tmp), free(word), tmp);
		}
		return (free(word), tmp);
	}
}

char	*expand_variables(char *line, t_config *config,
bool is_quoted, bool next_quoted)
{
	char	*word;
	char	*tmp;

	if (!line)
		return (NULL);
	word = line;
	if (ft_strchr(line, '$'))
		word = expand_dollar(line, config, is_quoted, next_quoted);
	if (word && is_quoted && ft_strchr(word, '*'))
	{
		tmp = word;
		word = ft_strjoin(ft_strdup("\006"), tmp);
		free(tmp);
		word = ft_strjoin(word, "\006");
	}
	return (word);
}

void	expand_command(char **command, t_config *config, bool is_quoted)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (ft_strchr(command[i], '$') || ft_strchr(command[i], '*'))
			command[i] = expand_variables(command[i], config, is_quoted, true);
		i++;
	}
	return ;
}
