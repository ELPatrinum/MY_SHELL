/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_something.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:19:37 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/12 11:26:18 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(char *command)
{
	char	*builtins[7];
	int		i;
	size_t	size;

	builtins[0] = "exit";
	builtins[1] = "echo";
	builtins[2] = "export";
	builtins[3] = "unset";
	builtins[4] = "pwd";
	builtins[5] = "cd";
	builtins[6] = "env";
	i = 0;
	while (i < 7)
	{
		size = ft_strlen(command);
		if (ft_strlen(builtins[i]) > size)
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(command, builtins[i], ft_strlen(command)))
			return (true);
		i++;
	}
	return (false);
}

bool	is_executable(t_lex *content_list)
{
	return (content_list->node_type == TOKEN_EXEC
		|| content_list->node_type == TOKEN_EXPR
		|| content_list->node_type == TOKEN_D_Q
		|| content_list->node_type == TOKEN_S_Q);
}

bool	is_redirection(t_type type)
{
	return (type >= 2 && type <= 5);
}

bool	check_next_quoted(t_content *content_list)
{
	return (content_list->next
		&& (content_list->next->node_type == TOKEN_D_Q
			|| content_list->next->node_type == TOKEN_S_Q));
}

bool	check_fail(t_lex **tokens_list, t_config *config)
{
	return (config->fail || !tokens_list || !(*tokens_list));
}
