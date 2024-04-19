/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:59:07 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/03/19 21:19:45 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_exit_code(char *str, char *command)
{
	if (command && !ft_strcmp(command, ".."))
		return (free(command), 127);
	if (ft_strstr(str, "No such file"))
		return (free(command), 127);
	if (ft_strstr(str, "Permission"))
	{
		if (command && !ft_strcmp(command, "."))
			return (free(command), 2);
		return (free(command), 126);
	}
	return (free(command), 1);
}

char	*get_command_path(t_config *config, char *command)
{
	char	*cmd_path;

	cmd_path = ft_getenv(config->env, "PATH");
	if (!cmd_path)
		cmd_path = ft_strdup(command);
	else
		cmd_path = find_path(command, cmd_path);
	if (!ft_strcmp(cmd_path, command)
		&& !access(command, F_OK) && !ft_strchr("./", command[0]))
	{
		put_error("minishell: ", command, ": command not found\n");
		free_garbage(config);
		free_array(config->env);
		exit(127);
	}
	if (!cmd_path)
	{
		free_garbage(config);
		free_array(config->env);
		exit(EXIT_FAILURE);
	}
	return (cmd_path);
}
