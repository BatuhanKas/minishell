/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:52:39 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/27 11:24:58 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

void	dollar_continue(char *cmd, size_t *i, size_t *j)
{
	while ((cmd[*i + *j] && ft_isalnum(cmd[*i + *j]))
		|| ((cmd[*i + *j] == '?') && (*i + *j) == *i + 1))
	{
		if (cmd[*i + *j] == '?')
		{
			(*j)++;
			break ;
		}
		else
			(*j)++;
	}
}

void	getenv_name(t_ms *ms, char *cmd, t_vars *vars, char **ret)
{
	vars->name = ft_substr(cmd, vars->i + 1, vars->j - 1);
	if (!vars->name)
		return (*ret = NULL, perror("malloc"));
	vars->full_name = find_env(ms->env, vars->name);
	free(vars->name);
	vars->i = vars->i + vars->j - 1;
	if (vars->full_name != NULL)
	{
		vars->tmp = ft_strjoin(*ret, vars->full_name);
		if (!vars->tmp)
			return (*ret = NULL, perror("malloc"));
	}
	else
	{
		vars->name = ft_strdup("");
		if (!vars->name)
			return (*ret = NULL, perror("malloc"));
		vars->tmp = ft_strjoin(*ret, vars->name);
		if (!vars->tmp)
			return (*ret = NULL, perror("malloc"));
		free(vars->name);
	}
	free(*ret);
	*ret = vars->tmp;
}

static int	join_char(t_vars *vars, char *cmd)
{
	vars->tmp2 = ft_substr(cmd, vars->i, 1);
	if (!vars->tmp2)
		return (1);
	vars->join = ft_strjoin(vars->ret, vars->tmp2);
	free(vars->tmp2);
	free(vars->ret);
	if (!vars->join)
		return (1);
	vars->ret = vars->join;
	return (0);
}

char	*dollar_parse(t_ms *ms, char *cmd)
{
	t_vars	vars;

	init_vars(&vars, 1);
	while (cmd[++vars.i])
	{
		handle_quote(cmd, &vars, 1, vars.i);
		handle_quote(cmd, &vars, 0, vars.i);
		quate_zero(&vars, cmd, vars.i);
		if (cmd[vars.i] && cmd[vars.i + 1] && cmd[vars.i] == '$'
			&& cmd[vars.i + 1] != ' ' && (!vars.quate))
		{
			if (handle_dollar(ms, &vars, cmd))
				return (NULL);
		}
		else
			if (join_char(&vars, cmd))
				return (NULL);
	}
	return (vars.ret);
}
