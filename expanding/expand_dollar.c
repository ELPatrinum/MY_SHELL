/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:54:37 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 11:24:11 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_simple(char *word, t_config *config, bool next_quoted)
{
	char	*tmp;
	char	*expand_tmp;
	int		i;

	i = 0;
	while (word[i] && word[i] != '$')
		i++;
	tmp = ft_substr(word, 0, i);
	if (!tmp)
		return (fail_config(config), free(word), NULL);
	expand_tmp = expand_word(ft_strdup(word + i), 0, config, next_quoted);
	free(word);
	tmp = ft_strjoin(tmp, expand_tmp);
	free(expand_tmp);
	return (tmp);
}

char	*expand_single(char *word, bool next_quoted)
{
	char	*tmp;

	if (next_quoted && word[0] == '$')
	{
		free(word);
		return (ft_strdup(""));
	}
	tmp = ft_strdup(word);
	free(word);
	return (tmp);
}

char	*expand_pid(char *word, int count, t_config *config, bool next_quoted)
{
	char	*expand_tmp;
	char	*tmp;

	expand_tmp = expand_word(ft_strdup(word + 1),
			count + 1, config, next_quoted);
	if (!expand_tmp)
		return (free(word), fail_config(config), NULL);
	tmp = ft_strjoin(ft_strdup("PID"), expand_tmp);
	free(expand_tmp);
	free(word);
	return (tmp);
}

char	*expand_word(char *word, int count, t_config *config, bool next_quoted)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (!word || !ft_strlen(word))
		return (word);
	if (ft_strlen(word) == 1 && ft_issymbol(word[0]) && count % 2 == 0)
		return (expand_single(word, next_quoted));
	if (word[i] != '$' && count % 2 == 0)
		return (expand_simple(word, config, next_quoted));
	else if (word[i] != '$')
		return (get_variable_value(config, word, i, next_quoted));
	else
	{
		if (count % 2)
			return (expand_pid(word, count, config, next_quoted));
		tmp = ft_strdup(word + 1);
		free(word);
		return (expand_word(tmp, count + 1, config, next_quoted));
	}
	return (free(word), NULL);
}

char	*expand_dollar(char *line, t_config *config,
bool is_quoted, bool next_quoted)
{
	char	*word;
	char	*tmp;
	char	**split_word;

	word = expand_word(line, 0, config, next_quoted);
	if (word && !is_quoted && ft_strchr(word, ' '))
	{
		split_word = ft_split(word, ' ');
		if (split_word && split_word[0] && split_word[1])
		{
			tmp = word;
			word = append_special(split_word);
			free(tmp);
			if (!word)
				return (fail_config(config), free_array(split_word), NULL);
		}
		free_array(split_word);
	}
	return (word);
}
