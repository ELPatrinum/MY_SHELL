/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:50:38 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/16 14:18:24 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_heredoc_command(t_content *content_list, char *command)
{
	char	*tmp;
	int		count;
	int		i;

	if (!ft_strchr(content_list->str, '$')
		|| content_list->node_type != TOKEN_EXEC)
		return (ft_strjoin(command, content_list->str));
	i = -1;
	count = 0;
	tmp = content_list->str;
	while (tmp[++i])
	{
		if (tmp[i] != '$')
			break ;
		count++;
	}
	if (!tmp[i] && !content_list->next)
		return (ft_strjoin(command, tmp));
	if (!(count % 2) || tmp[i])
		return (ft_strjoin(command, content_list->str));
	if (count == 1)
		return (command);
	tmp = ft_substr(content_list->str, 0, count - 1);
	command = ft_strjoin(command, tmp);
	return (free(tmp), command);
}

int	execute_redir_hd(t_config *config, t_tree *tree)
{
	int	fds[2];

	if (pipe(fds) < 0)
		return (fail_config(config), 0);
	write(fds[1], tree->buffer, ft_strlen(tree->buffer));
	close(fds[1]);
	if (dup2(fds[0], STDIN_FILENO) < 0)
		return (fail_config(config), 0);
	close(fds[0]);
	return (1);
}

void	read_save(t_tree *tree, t_config *config, char *line, char **buffer)
{
	g_here_flag[0] = 0;
	while (line)
	{
		free(line);
		signal(SIGINT, &sig_herdoc);
		line = readline("> ");
		if (!line || (ft_strlen(tree->filename) == ft_strlen(line)
				&& !ft_strncmp(line, tree->filename, ft_strlen(line))))
			break ;
		if (ft_strchr(line, '$') && ft_strlen(line) > 1 && tree->expand_heredoc)
			line = expand_variables(line, config, true, false);
		line = ft_strjoin(line, "\n");
		if (!line)
			break ;
		(*buffer) = ft_strjoin((*buffer), line);
		if (!(*buffer))
			break ;
	}
	dup2(config->std_in, 0);
	signal(SIGINT, &sig_int);
	(free(line));
}

void	execute_heredoc(t_tree *tree, t_config *config)
{
	char	**tmp;
	char	*buffer;
	char	*line;

	buffer = ft_strdup("");
	if (!buffer)
		return (fail_config(config));
	line = ft_strdup("");
	tmp = get_command(config, tree->content_list, 'h');
	if (!tmp || !tmp[0])
		return (free(tmp), fail_config(config));
	tree->filename = ft_strdup(tmp[0]);
	free_array(tmp);
	read_save(tree, config, line, &buffer);
	if (g_here_flag[0])
	{
		free(buffer);
		buffer = NULL;
	}
	tree->buffer = buffer;
	(config->heredocs_executed)++;
}

void	traverse_heredoc(t_tree *tree, t_config *config, int order)
{
	if (!tree || config->fail || g_here_flag[0]
		|| (config->heredocs_to_execute
			&& config->heredocs_executed >= config->heredocs_to_execute))
		return ;
	if (tree->node_type == TOKEN_HEREDOC && tree->heredoc_read)
		return ;
	if (tree->node_type == TOKEN_HEREDOC && tree->heredoc_order == order)
	{
		execute_heredoc(tree, config);
		traverse_heredoc(tree->left, config, order + 1);
		traverse_heredoc(tree->right, config, order + 1);
	}
	else
	{
		traverse_heredoc(tree->left, config, order);
		traverse_heredoc(tree->right, config, order);
		if (tree->node_type == TOKEN_HEREDOC)
			execute_heredoc(tree, config);
	}
}
