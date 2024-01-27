/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:34:41 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/23 13:35:33 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int	update_env(t_env *envp, char *name, char *value)
{
	t_env	*tmp;

	if (!value)
		return (0);
	tmp = envp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(value);
			if (!tmp->value)
				return (perror("Malloc"), 1);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	add_env(t_env **envp, char *name, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *envp;
	if (has_env(*envp, name))
		return (update_env(*envp, name, value));
	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("Malloc"), 1);
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (!tmp)
	{
		*envp = new;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

void	update_exit_code(t_ms *ms)
{
	char	*tmp;

	if (g_signal == 130)
		ms->status = 130;
	else if (g_signal == 131)
		ms->status = 131;
	tmp = ft_itoa(ms->status);
	update_env(ms->env, "?", tmp);
	free(tmp);
}

int	env(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "?"))
		{
			if (tmp->value)
			{
				ft_putstr_fd(tmp->name, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd(tmp->value, 1);
				ft_putstr_fd("\n", 1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
