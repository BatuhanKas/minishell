/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:27:16 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/19 10:15:47 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>

static char	*env_path(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "PATH"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*path_loop(t_ms *ms, char *cmd)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (ms->path[i])
	{
		tmp = ft_strjoin(ms->path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(tmp2, X_OK) == 0)
		{
			ft_full_free(ms->path);
			return (tmp2);
		}
		free(tmp2);
		i++;
	}
	return (ft_full_free(ms->path), NULL);
}

char	*find_path(t_ms *ms, char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	ms->path_tmp = env_path(ms->env);
	if (!ms->path_tmp)
		return (NULL);
	ms->path = ft_split(ms->path_tmp, ':');
	return (path_loop(ms, cmd));
}
