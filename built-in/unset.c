/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:46:55 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/27 12:14:49 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	remove_env(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	unset(char **argv, t_ms *ms)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (has_env(ms->export, argv[i]))
			remove_env(&ms->export, argv[i]);
		if (has_env(ms->env, argv[i]))
			remove_env(&ms->env, argv[i]);
		i++;
	}
	return (0);
}
