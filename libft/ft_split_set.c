/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:39:19 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/10 18:47:34 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_sep(char *sep, char c)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_wdcount(char *str, char *sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_is_sep(sep, str[i]))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && !ft_is_sep(sep, str[i]))
			i++;
	}
	return (count);
}

int	ft_wlen(char *str, char *sep)
{
	int	i;

	i = 0;
	while (str[i] && !ft_is_sep(sep, str[i]))
		i++;
	return (i);
}

char	*ft_word(char *str, char *sep)
{
	int		i;
	int		wlen;
	char	*word;

	i = 0;
	wlen = ft_wlen(str, sep);
	word = (char *) malloc((wlen + 1) * sizeof(char));
	while (i < wlen)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_set(char *str, char *charset)
{
	int		i;
	int		j;
	int		wd_count;
	char	**strings;

	wd_count = ft_wdcount(str, charset);
	strings = (char **)malloc((wd_count + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && ft_is_sep(charset, str[i]))
			i++;
		if (str[i] != '\0')
		{
			strings[j] = ft_word((str + i), charset);
			j++;
		}
		while (str[i] && !ft_is_sep(charset, str[i]))
			i++;
	}
	strings[j] = 0;
	return (strings);
}
