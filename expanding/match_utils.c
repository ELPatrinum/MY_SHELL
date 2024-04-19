/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:37:15 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/11 12:58:45 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_word_finished(char *pattern, int i)
{
	while (pattern[i] && pattern[i] == '*')
		i++;
	if (!pattern[i])
		return (true);
	return (false);
}

bool	advance_pattern(char *pattern, int *i, bool *in_quotes)
{
	while (pattern[*i] && pattern[*i] == '*')
		(*i)++;
	if (!pattern[*i])
		return (true);
	while (pattern[*i] == 6)
	{
		(*in_quotes) = !(*in_quotes);
		(*i)++;
	}
	if (!pattern[*i])
		return (true);
	return (false);
}

bool	set_inquotes(int *i, bool *in_quotes)
{
	(*in_quotes) = !(*in_quotes);
	(*i)++;
	return (true);
}
