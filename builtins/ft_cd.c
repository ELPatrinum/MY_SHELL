/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:32:32 by muel-bak          #+#    #+#             */
/*   Updated: 2024/04/14 16:54:22 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_option(int option, char **env, char **env_value)
{
	if (option == CD_HOME)
	{
		*env_value = ft_getenv(env, "HOME");
		if (!*env_value)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (1);
		}
	}
	else if (option == CD_OLDPWD)
	{
		*env_value = ft_getenv(env, "OLDPWD");
		if (!*env_value)
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_update_faile(char ***env, char *arg)
{
	char	*env_value;
	char	*dir;

	env_value = NULL;
	env_value = ft_getenv(*env, "PWD");
	write(2, CD_RROR, 58);
	perror("");
	dir = ft_strjoin(ft_strdup(ft_getenv(*env, "PWD")), "/");
	dir = ft_strjoin(dir, arg);
	if (update_oldpwd_pwd(*env, env_value, dir) != 0)
	{
		free(dir);
		return (1);
	}
	free(dir);
	return (0);
}

static int	change_directory(int option, char **env)
{
	int		ret;
	char	*env_value;

	env_value = NULL;
	if (cd_option(option, env, &env_value) == 1)
		return (1);
	ret = chdir(env_value);
	if (ret < 0)
	{
		print_cd_error();
		return (1);
	}
	return (0);
}

int	ft_cd(char *args, char **env, bool *flag)
{
	int		cd_ret;
	char	*dir;

	if (!args)
		return (change_directory(CD_HOME, env));
	dir = getcwd(NULL, 0);
	if (!dir && !ft_strcmp(args, "..") && !(*flag))
	{
		write(2, "minishell : cd: ..: No such file or directory\n", 47);
		*flag = true;
		return (1);
	}
	if (!dir && !ft_strcmp(args, "..") && (*flag))
		return (cd_ret = chdir(args), 3);
	if (ft_strcmp(args, "-") == 0)
		cd_ret = change_directory(CD_OLDPWD, env);
	else
	{
		cd_ret = chdir(args);
		if (cd_ret < 0)
			return (free(dir), print_cd_error(), 1);
	}
	free(dir);
	return (0);
}
