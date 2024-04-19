/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:29:56 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/11 12:58:49 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	advance_index(char *pattern, char *word, int *i, int *j)
{
	int	similar_count;

	similar_count = 0;
	while (pattern[*i] && pattern[*i] == pattern[*i + 1])
	{
		(*i)++;
		similar_count++;
	}
	if (pattern[*i + 1] != '*')
	{
		while (word[*j] && word[*j] == word[*j + 1])
		{
			(*j)++;
			similar_count--;
		}
		if (similar_count > 0)
			return (false);
	}
	(*i)++;
	(*j)++;
	return (true);
}

static bool	verify_check(char *pattern, char *word, int j, int i)
{
	if (word[j])
	{
		while (i >= 0 && pattern[i] != '*')
			i--;
		return (check_match(pattern + i, word + j));
	}
	return (true);
}

static void	init_vars(int *i, int *j, bool *res, bool *in_quotes)
{
	*i = 0;
	*j = 0;
	*res = true;
	*in_quotes = false;
}

bool	check_match(char *pattern, char *word)
{
	int		i;
	int		j;
	bool	res;
	bool	in_quotes;

	init_vars(&i, &j, &res, &in_quotes);
	while (pattern[i])
	{
		if (!word[j])
			return (check_word_finished(pattern, i));
		if (pattern[i] == 6 && set_inquotes(&i, &in_quotes))
			continue ;
		if (pattern[i] != '*' || in_quotes)
		{
			if (word[j] == pattern[i] && advance_index(pattern, word, &i, &j))
				continue ;
			else
				return (false);
		}
		if (advance_pattern(pattern, &i, &in_quotes))
			return (true);
		while (word[j] && word[j] != pattern[i])
			j++;
	}
	return (verify_check(pattern, word, j, i));
}
