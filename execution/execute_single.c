/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:00:02 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/14 16:56:07 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_single(t_config *config)
{
	int	check;
	int	status;

	check = execute_command(config);
	wait(&status);
	if (check == 0)
	{
		if (WIFSIGNALED(status))
		{
			if (status == 2)
				return (130);
			if (status == 3)
			{
				reset_terminal();
				rl_on_new_line();
				rl_replace_line("", 1);
				printf("Quit: 3\n");
				return (131);
			}
		}
	}
	return (WEXITSTATUS(status));
}

static void	print_command_error(char *command)
{
	if (!ft_strlen(command))
		put_error("minishell: ", command, ": command not found\n");
	else if (ft_strlen(command) == 1 && command[0] == '.')
		put_error("minishell: ", command, ": filename argument required\n");
	else if (ft_strlen(command) == 2 && !ft_strcmp(command, ".."))
		put_error("minishell: ", command, ": command not found\n");
	else if (access(command, F_OK) && ft_strchr("./", command[0]))
		put_error("minishell: ", command, ": No such file or directory\n");
	else if (access(command, F_OK))
		put_error("minishell: ", command, ": command not found\n");
	else
		put_error("minishell: ", command, ": Permission denied\n");
}

void	fork_execute(t_config *config, t_tree *tree)
{
	char	**args;
	char	*cmd_path;

	signal(SIGINT, &sig_int);
	args = (tree)->command;
	cmd_path = NULL;
	if (args && (ft_strlen(args[0]) || (tree)->node_type == TOKEN_D_Q
			|| (tree)->node_type == TOKEN_S_Q))
	{
		cmd_path = get_command_path(config, args[0]);
		free(args[0]);
		args[0] = cmd_path;
		execve(args[0], args, config->env);
		print_command_error(args[0]);
		if (ft_strncmp(args[0], cmd_path, ft_strlen(cmd_path)))
			free(cmd_path);
	}
	if (!ft_strlen(cmd_path) && !((tree)->node_type == TOKEN_D_Q
			|| (tree)->node_type == TOKEN_S_Q))
		(free_garbage(config), free_array(config->env), exit(0));
	cmd_path = ft_strdup(args[0]);
	free_garbage(config);
	free_array(config->env);
	exit(get_exit_code(strerror(errno), cmd_path));
}

int	execute_command(t_config *config)
{
	t_tree	*tree;
	pid_t	pid;
	int		status;

	tree = config->tree;
	if (!tree || config->fail)
		return (0);
	(tree)->command = get_command(config, (tree)->content_list, 'c');
	tree->command_tmp = tree->command;
	if (!(tree)->command)
		return (0);
	if (is_builtin((tree)->command[0]))
	{
		status = execute_builtin(config);
		pid = fork();
		if (!pid)
			exit(status);
		return (status);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
		fork_execute(config, tree);
	return (0);
}
