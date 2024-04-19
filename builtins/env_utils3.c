/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:11:30 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/19 19:47:04 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fail_free(char ***env, int i)
{
	int	j;

	if ((*env)[i] == NULL)
	{
		j = 0;
		while (j < i)
			free((*env)[j++]);
		free(*env);
		return (0);
	}
	return (1);
}

char	**allocate_environment(char **real_env)
{
	int		count;
	int		i;
	char	**env;

	count = 0;
	while (real_env[count] != NULL)
		count++;
	env = (char **) malloc((count + 1) * sizeof(char *));
	if (env == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		env[i] = ft_strdup(real_env[i]);
		if (!fail_free(&env, i))
			return (NULL);
		i++;
	}
	env[count] = NULL;
	return (env);
}

void	free_list_null(t_env **list)
{
	free_env_list(*list);
	*list = NULL;
}
