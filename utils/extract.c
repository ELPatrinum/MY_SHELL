/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:14:04 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 12:48:01 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	finish_content_part(char ***res, char **command,
t_config *config, t_content **content_list)
{
	char	**tmp;

	if (!ft_strlen(*command) && !config->content_quoted)
	{
		(*content_list) = (*content_list)->next;
		config->command_in = false;
		return (true);
	}
	tmp = *res;
	tmp = append_command(tmp, *command, config);
	if (!(*tmp))
		return (fail_config(config), free(*command), false);
	*command = ft_strdup("");
	(*content_list) = (*content_list)->next;
	config->command_in = false;
	config->content_quoted = false;
	*res = tmp;
	return (true);
}

static void	init_vars(char ***res, char **command, t_config *config)
{
	*res = NULL;
	*command = ft_strdup("");
	config->command_in = false;
	config->content_quoted = false;
}

char	**get_command(t_config *config, t_content *content_list, char op)
{
	char	**res;
	char	*command;

	init_vars(&res, &command, config);
	while (content_list && command && !config->fail)
	{
		if ((int)content_list->node_type == -1
			&& finish_content_part(&res, &command, config, &content_list))
			continue ;
		if (op == 'h')
			command = get_heredoc_command(content_list, command);
		else if (content_list->node_type == TOKEN_S_Q)
			command = guard_command(command, content_list);
		else
			command = get_normal_command(content_list, config, command, op);
		config->command_in = true;
		content_list = content_list->next;
	}
	if (!command || config->fail)
		return (fail_config(config), free(command), free_array(res), NULL);
	if (!config->command_in && command && !ft_strlen(command))
		free(command);
	else
		res = append_command(res, command, config);
	return (handle_finish(config, res, op));
}

t_content	*get_content_list(t_config *config, char op)
{
	t_content	*res;
	t_content	*tmp;
	t_lex		**tokens_list;

	tokens_list = &(config->tokens_list);
	if (check_fail(tokens_list, config) || !is_executable(*tokens_list))
		return (NULL);
	res = eval_content((*tokens_list)->content);
	if (!res)
		return (fail_config(config), NULL);
	(*tokens_list) = (*tokens_list)->next;
	if (op == 'f')
		return (res);
	while ((*tokens_list) && is_executable(*tokens_list))
	{
		append_content_node(&res, NULL, -1);
		if (!res)
			return (fail_config(config), NULL);
		tmp = res;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = eval_content((*tokens_list)->content);
		(*tokens_list) = (*tokens_list)->next;
	}
	return (res);
}
