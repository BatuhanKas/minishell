/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:39:06 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/12 15:44:36 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int	sort_export(t_env **envp, char *temp_name, char *temp_value)
{
	t_env	*tmp;
	int		changed;

	tmp = *envp;
	changed = 1;
	while (changed)
	{
		changed = 0;
		tmp = *envp;
		while (tmp && tmp->next)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
			{
				temp_name = tmp->name;
				temp_value = tmp->value;
				tmp->name = tmp->next->name;
				tmp->value = tmp->next->value;
				tmp->next->name = temp_name;
				tmp->next->value = temp_value;
				changed = 1;
			}
			tmp = tmp->next;
		}
	}
	return (print_export(envp));
}

int	print_export(t_env **envp)
{
	t_env	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "?"))
		{
			if (tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			else
				printf("declare -x %s\n", tmp->name);
		}
		tmp = tmp->next;
	}
	return (0);
}
