/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:43:33 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/13 14:59:11 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*handle_regular_token(char *str, const char *delim, char **last)
{
	char	*token;

	token = str;
	while (*str && !ft_strchr(delim, *str) && ft_strncmp(str, "&&", 2) != 0
		&& ft_strncmp(str, "||", 2) != 0 && ft_strncmp(str, "<<", 2) != 0)
	{
		if (*str == '(' || *str == ')')
			break ;
		str++;
	}
	if (token != str)
		return (*last = str, token);
	if (*str == '\0')
		return (*last = str, token);
	if (ft_strncmp(str, "&&", 2) == 0 || ft_strncmp(str, "||", 2) == 0
		|| ft_strncmp(str, "<<", 2) == 0)
	{
		*last = str + 2;
		return (token);
	}
	*last = str + 1;
	return (token);
}

static char	*handle_operator(char *str, char **last)
{
	if (*str == '<' && *(str + 1) == '<')
		return (*last = str + 2, "<<");
	if (*str == '>' && *(str + 1) == '>')
		return (*last = str + 2, ">>");
	if (*str == '<' && *(str + 1) != '<')
		return (*last = str + 1, "<");
	if (*str == '>' && *(str + 1) != '>')
		return (*last = str + 1, ">");
	else if (*str == '&' && *(str + 1) == '&')
	{
		*last = str + 2;
		return ("&&");
	}
	else if (*str == '|' && *(str + 1) == '|')
	{
		*last = str + 2;
		return ("||");
	}
	else if (*str == '|' && *(str + 1) != '|')
	{
		*last = str + 1;
		return ("|");
	}
	return (NULL);
}

static char	*handle_parentheses(char *str, char **last)
{
	char	*token;

	token = NULL;
	if (*str == '(')
		token = "(";
	else if (*str == ')')
		token = ")";
	if (token)
		*last = str + 1;
	return (token);
}

static char	*handle_quotes(char *str, char **last, bool *flag)
{
	char	quote;
	char	*token;
	int		check;

	check = 0;
	token = NULL;
	if (*str == '"' || *str == '\'')
	{
		quote = *str;
		check++;
		str++;
		token = str;
		while (*str && *str != quote)
			str++;
		if (*str == quote)
			check++;
		if (check == 2)
			*flag = true;
		if (*str == '\0')
			return (*last = str, token);
		*str = '\0';
		*last = str + 1;
		return (token);
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim, bool *flag)
{
	static char	*last;
	char		*token;

	if (str == NULL)
		str = last;
	if (!str)
		return (NULL);
	while (*str && ft_strchr(delim, *str))
		str++;
	if (*str == '\0')
		return (NULL);
	token = handle_operator(str, &last);
	if (token)
		return (token);
	token = handle_parentheses(str, &last);
	if (token)
		return (token);
	token = handle_quotes(str, &last, flag);
	if (token)
		return (token);
	return (handle_regular_token(str, delim, &last));
}
