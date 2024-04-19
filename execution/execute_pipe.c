/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:00:47 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 13:48:23 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_pipe_left(t_config *config,
pid_t pid, int *tunnel, t_tree *tree)
{
	int	status;

	if (pid < 0)
		exit(EXIT_FAILURE);
	signal(SIGINT, SIG_IGN);
	if (!pid)
	{
		signal(SIGINT, &sig_int);
		close(tunnel[0]);
		dup2(tunnel[1], STDOUT_FILENO);
		close(tunnel[1]);
		config->tree = (tree)->left;
		status = execute_cmdline(config);
		free_garbage(config);
		exit(status);
	}
	close(tunnel[1]);
}

static void	execute_pipe_right(t_config *config, pid_t pid, t_tree *tree)
{
	int	status;

	if (pid < 0)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		config->tree = (tree)->right;
		signal(SIGINT, &sig_int);
		status = execute_cmdline(config);
		free_garbage(config);
		exit(status);
	}
	close(STDIN_FILENO);
}

int	execute_pipe(t_config *config)
{
	t_tree	*tree;
	int		tunnel[2];
	pid_t	pid;
	int		status;
	int		ret;

	tree = config->tree;
	if (!tree)
		return (0);
	pipe(tunnel);
	pid = fork();
	execute_pipe_left(config, pid, tunnel, tree);
	dup2(tunnel[0], STDIN_FILENO);
	close(tunnel[0]);
	pid = fork();
	execute_pipe_right(config, pid, tree);
	waitpid(pid, &status, 0);
	ret = WEXITSTATUS(status);
	while (wait(&status) > 0)
		signal(SIGINT, &handleint);
	return (ret);
}
