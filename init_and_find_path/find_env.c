/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:54:13 by melihyil          #+#    #+#             */
/*   Updated: 2023/12/07 18:48:54 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	*find_env(t_env *envp, char *name)
{
	t_env	*env;

	env = envp;
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	has_env(t_env *envp, char *name)
{
	t_env	*env;

	env = envp;
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (1);
		env = env->next;
	}
	return (0);
}
