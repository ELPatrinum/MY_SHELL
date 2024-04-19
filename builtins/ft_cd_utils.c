/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:22:41 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/20 03:05:23 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_indx(char **env, char **old_ev, char **pwd, int (*pwd_ix)[2])
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			*old_ev = env[i];
			(*pwd_ix)[0] = i;
		}
		else if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			*pwd = env[i];
			(*pwd_ix)[1] = i;
		}
		i++;
	}
}

static void	init_(char **oldpwd_env, char **pwd_env,
int (*pwd_ix)[2], char **env)
{
	(*pwd_ix)[0] = -1;
	(*pwd_ix)[1] = -1;
	*oldpwd_env = NULL;
	*pwd_env = NULL;
	get_indx(env, oldpwd_env, pwd_env, pwd_ix);
}

int	update_oldpwd_pwd(char **env, const char *oldpwd, const char *pwd)
{
	char	*oldpwd_env;
	char	*tmp;
	char	*pwd_env;
	int		pwd_ix[2];

	init_(&oldpwd_env, &pwd_env, &pwd_ix, env);
	if (pwd_ix[0] != -1)
	{
		tmp = ft_strjoin(ft_strdup("OLDPWD="), oldpwd);
		if (!tmp)
			return (1);
		ft_free(oldpwd_env);
		env[pwd_ix[0]] = tmp;
	}
	if (pwd_ix[1] != -1)
	{
		tmp = ft_strjoin(ft_strdup("PWD="), pwd);
		if (!tmp)
			return (1);
		ft_free(pwd_env);
		env[pwd_ix[1]] = tmp;
	}
	if (pwd_ix[0] != -1 || pwd_ix[1] != -1)
		return (0);
	return (1);
}

static int	update_it(char ***env)
{
	char	*env_value;
	char	cwd[PATH_MAX];

	env_value = NULL;
	env_value = ft_getenv(*env, "PWD");
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (update_oldpwd_pwd(*env, env_value, cwd) != 0)
		return (1);
	return (0);
}

void	ft_update(char ***env)
{
	update_it(env);
}
