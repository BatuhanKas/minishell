/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:18:59 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/18 16:14:01 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	built_in(char **argv, t_ms *ms)
{
	int	stats;

	stats = -1;
	if (!ft_strcmp(argv[0], "echo"))
		stats = echo(argv);
	else if (!ft_strcmp(argv[0], "cd"))
		stats = cd(ms, argv);
	else if (!ft_strcmp(argv[0], "pwd"))
		stats = pwd();
	else if (!ft_strcmp(argv[0], "export"))
		stats = export(argv, ms);
	else if (!ft_strcmp(argv[0], "unset"))
		stats = unset(argv, ms);
	else if (!ft_strcmp(argv[0], "env"))
		stats = env(ms->env);
	else if (!ft_strcmp(argv[0], "exit"))
		stats = exit_shell(argv, ms);
	return (stats);
}
