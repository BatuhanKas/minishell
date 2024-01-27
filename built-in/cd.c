/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:18:53 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/23 19:52:31 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	cd(t_ms *ms, char **argv)
{
	char	*tmp;

	if (!argv[1] || !ft_strcmp(argv[1], "~"))
	{
		if (find_env(ms->env, "HOME") == NULL)
			return (ft_putendl_fd("cd: HOME not set", 2), 1);
		if (chdir(find_env(ms->env, "HOME")) == -1)
			return (print_error(find_env(ms->env, "HOME"), strerror(errno)), 1);
	}
	else if (!ft_strcmp(argv[1], "-"))
	{
		if (chdir(find_env(ms->env, "OLDPWD")) == -1)
			return (ft_putendl_fd("cd: OLDPWD not set", 2), 1);
	}
	else if (chdir(argv[1]) == -1)
		return (ft_putstr_fd("minishell: cd: ", 2),
			ft_putstr_fd(argv[1], 2),
			ft_putendl_fd(": No such file or directory", 2), 1);
	tmp = getcwd(NULL, 0);
	add_env(&ms->env, "OLDPWD", find_env(ms->env, "PWD"));
	add_env(&ms->export, "OLDPWD", find_env(ms->env, "PWD"));
	add_env(&ms->env, "PWD", tmp);
	add_env(&ms->export, "PWD", tmp);
	free(tmp);
	return (0);
}
