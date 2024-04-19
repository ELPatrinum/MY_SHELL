/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:35:24 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 16:56:20 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree->buffer);
	free(tree->filename);
	free_array(tree->command_tmp);
	free_content_list(tree->content_list);
	free(tree);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		free(env->full);
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_garbage(t_config *config)
{
	free_tree(config->tmp_tree);
	config->tmp_tree = NULL;
	free(config->tmp_line);
	config->tmp_line = NULL;
	free_lex_list(&config->tmp_list);
	config->tmp_list = NULL;
	free_env_list(config->env_list);
	config->env_list = NULL;
	if (config->std_in != -1)
	{
		close(config->std_in);
		close(config->std_out);
	}
	free(config->tmp);
	config->tmp = NULL;
	free(config->error_msg);
	config->error_msg = NULL;
}
