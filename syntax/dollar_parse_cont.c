/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse_cont.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:38:56 by bkas              #+#    #+#             */
/*   Updated: 2024/01/19 14:08:59 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

void	init_vars(t_vars *vars, int flag)
{
	vars->nail = 0;
	if (flag)
		vars->i = -1;
	else
		vars->i = 0;
	vars->j = 0;
	vars->q = 0;
	vars->q2 = 0;
	vars->quate = 0;
	vars->quate2 = 0;
	vars->ret = NULL;
	vars->tmp = NULL;
	vars->tmp2 = NULL;
	vars->cmd = NULL;
	vars->join = NULL;
	vars->count = 0;
	vars->k = 0;
	vars->c = 0;
}

void	quate_zero(t_vars *vars, char *cmd, size_t k)
{
	if (cmd[k] == '\'' && vars->quate == 2)
		vars->quate = 0;
	else if (cmd[k] == '"' && vars->quate2 == 2)
		vars->quate2 = 0;
}

void	handle_quote(char *cmd, t_vars *vars, int flag, size_t i)
{
	if (flag && cmd[i]
		&& cmd[i] == '"' && vars->quate == 0)
	{
		vars->quate2 += 1;
		vars->q2 = i;
	}
	else if (!flag && cmd[i] && cmd[i] == '\''
		&& !vars->quate2)
	{
		vars->quate += 1;
		vars->q = i;
	}
}

int	handle_dollar(t_ms *ms, t_vars *vars, char *cmd)
{
	vars->j = 1;
	dollar_continue(cmd, &vars->i, &vars->j);
	getenv_name(ms, cmd, vars, &vars->ret);
	if (!(vars->ret))
		return (perror("malloc"), 1);
	return (0);
}
