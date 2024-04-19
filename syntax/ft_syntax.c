/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:57:05 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/20 00:50:18 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_free_list(t_tok *tokens)
{
	t_tok	*temp;

	while (tokens != NULL)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

static int	min_value(int *array, int size)
{
	int	min;
	int	i;

	min = array[0];
	i = 1;
	while (i < size)
	{
		if (array[i] < min)
			min = array[i];
		i++;
	}
	return (min);
}

static bool	my_print_error(int c, bool *printed, char ***error)
{
	if (c == 1)
	{
		*printed = true;
		**error = ft_strdup("Syntax error : related to Parenthese\n");
	}
	else if (c == 2)
	{
		*printed = true;
		**error = ft_strdup("Syntax error : related to a token\n");
	}
	else if (c == 3)
	{
		*printed = true;
		**error = ft_strdup("Syntax error : related to Redir\n");
	}
	else if (c == 4)
	{
		*printed = true;
		**error = ft_strdup("Syntax error : related to redir\n");
	}
	return (false);
}

bool	check_syn(char *line)
{
	if (!closed_quotes((char *)line))
	{
		write(2, "Syntax error : related to unclosed Quotes \n", 44);
		return (false);
	}
	return (true);
}

bool	ft_syntax(const char *line, int *heredoc_value, char **error_to_print)
{
	int		heredoc[6];
	bool	printed;
	bool	returned;
	t_tok	*tokens;

	(1 == 1) && (heredoc[0] = 0, heredoc[1] = 0, heredoc[2] = 0);
	(1 == 1) && (heredoc[3] = 0, heredoc[4] = 0);
	(1 == 1) && (returned = true, printed = false);
	tokens = syn_tokenize((char *)line);
	if (!line || !*line)
		return (true);
	if (!check_redir_in_out(tokens, &heredoc[4]) && !printed)
		returned = my_print_error(4, &printed, &error_to_print);
	if (!closed_parentheses(tokens, &heredoc[0]) && !printed)
		returned = my_print_error(1, &printed, &error_to_print);
	if (!check_parenthese(tokens, &heredoc[1]) && !printed)
		returned = my_print_error(1, &printed, &error_to_print);
	if ((!check_start_end_tokens(tokens, &heredoc[2]) && !printed)
		|| (!check_tokens(tokens, &heredoc[5]) && !printed))
		returned = my_print_error(2, &printed, &error_to_print);
	if (!check_redir_before_bracket(tokens, &heredoc[3]) && !printed)
		returned = my_print_error(3, &printed, &error_to_print);
	if (!returned)
		*heredoc_value = min_value(heredoc, 6);
	return (my_free_list(tokens), returned);
}
