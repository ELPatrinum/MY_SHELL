/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:58:43 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 11:29:55 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_special(t_config *config, char *word, bool next_quoted)
{
	char	*expand_tmp;
	char	*tmp;

	if (!word || config->fail)
		return (free(word), NULL);
	expand_tmp = expand_word(ft_strdup(word + 1), 0, config, next_quoted);
	tmp = ft_strjoin(ft_strdup(""), expand_tmp);
	free(word);
	free(expand_tmp);
	return (tmp);
}

char	*expand_point_exit(t_config *config,
char *word, int i, bool next_quoted)
{
	if (!word || config->fail)
		return (free(word), NULL);
	if (word[i] == '?')
		return (expand_exit_status(config, word, next_quoted));
	else if (ft_strchr(".=", word[i]))
		return (expand_point(config, word, next_quoted));
	return (free(word), NULL);
}

char	*expand_exit_status(t_config *config, char *word, bool next_quoted)
{
	char	*buff;
	char	*tmp;
	char	*expand_tmp;

	if (!word || config->fail)
		return (free(word), NULL);
	buff = ft_itoa(config->last_status);
	if (!buff)
		return (fail_config(config), free(word), NULL);
	expand_tmp = expand_word(ft_strdup(word + 1), 0, config, next_quoted);
	tmp = ft_strjoin(buff, expand_tmp);
	free(word);
	free(expand_tmp);
	return (tmp);
}

char	*expand_point(t_config *config, char *word, bool next_quoted)
{
	char	*tmp;
	char	*expand_tmp;

	if (!word || config->fail)
		return (free(word), NULL);
	expand_tmp = expand_word(ft_strdup(word + 1), 0, config, next_quoted);
	tmp = append_char(ft_strdup("$"), *word);
	tmp = ft_strjoin(tmp, expand_tmp);
	free(word);
	free(expand_tmp);
	return (tmp);
}
