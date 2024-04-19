/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:31:50 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/16 13:30:18 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_redir_in(t_config *config, t_tree *tree)
{
	int		fd;
	char	*tmp_str;

	tmp_str = ft_strjoin(ft_strdup("minishell: "), tree->filename);
	if (!tmp_str)
		return (fail_config(config), 0);
	fd = open(tree->filename, O_RDONLY, 0644);
	if (fd < 0)
		perror(tmp_str);
	free(tmp_str);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (fail_config(config), 0);
	close(fd);
	return (1);
}

int	execute_redir_out(t_config *config, t_tree *tree)
{
	int		fd;
	char	*tmp_str;

	tmp_str = ft_strjoin(ft_strdup("minishell: "), tree->filename);
	if (!tmp_str)
		return (fail_config(config), 0);
	fd = open(tree->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror(tmp_str);
	free(tmp_str);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (fail_config(config), 0);
	close(fd);
	return (1);
}

int	execute_redir_append(t_config *config, t_tree *tree)
{
	int		fd;
	char	*tmp_str;

	tmp_str = ft_strjoin(ft_strdup("minishell: "), tree->filename);
	if (!tmp_str)
		return (fail_config(config), 0);
	fd = open(tree->filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror(tmp_str);
	free(tmp_str);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (fail_config(config), 0);
	close(fd);
	return (1);
}

int	execute_redir_helper(t_config *config, t_tree *tree)
{
	char	**words;

	if (config->fail)
		return (0);
	words = NULL;
	if (tree->node_type != TOKEN_HEREDOC)
		words = get_command(config, tree->content_list, 'f');
	if (tree->node_type != TOKEN_HEREDOC && !words)
	{
		put_error("minishell: ", tree->content_list->str,
			": ambiguous redirect\n");
		return (fail_config(config), 0);
	}
	if (words)
		tree->filename = ft_strdup(words[0]);
	free_array(words);
	if (tree->node_type == TOKEN_REDIR_IN)
		return (execute_redir_in(config, tree));
	else if (tree->node_type == TOKEN_REDIR_OUT)
		return (execute_redir_out(config, tree));
	else if (tree->node_type == TOKEN_REDIR_APPEND)
		return (execute_redir_append(config, tree));
	else
		return (execute_redir_hd(config, tree));
	return (1);
}

void	execute_redir(t_config *config)
{
	t_tree	*tree;
	t_tree	*tmp;

	tree = config->tree;
	if (!tree)
		return ;
	tmp = tree;
	while (tmp && tmp->node_type >= 2 && tmp->node_type <= 5)
	{
		if (!execute_redir_helper(config, tmp) || config->fail)
			return ;
		tmp = tmp->left;
	}
	config->tree = tmp;
}
