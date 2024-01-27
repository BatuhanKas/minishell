/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:18:38 by bkas              #+#    #+#             */
/*   Updated: 2024/01/27 11:33:14 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	is_null(t_vars *vars)
{
	vars->cmd[vars->k] = ft_strdup(vars->tmp);
	if (!vars->cmd[vars->k])
		return (1);
	vars->k++;
	ft_strclr(vars->tmp);
	return (2);
}

static int	copy_cmd(t_vars *vars, int flag)
{
	if (flag)
	{
		vars->cmd[vars->k] = ft_strdup(vars->tmp);
		if (!vars->cmd[vars->k])
			return (1);
		vars->k++;
		vars->i++;
		ft_strclr(vars->tmp);
	}
	else
	{
		vars->cmd[vars->k] = ft_strdup("");
		if (!vars->cmd[vars->k])
			return (1);
		vars->k++;
		vars->i++;
	}
	return (0);
}

int	in_nail(t_vars *vars, char *str)
{
	int	flag;

	flag = 0;
	vars->nail = str[vars->i];
	vars->i++;
	if (str[vars->i] == vars->nail && is_separator(str[vars->i + 1]))
		return (copy_cmd(vars, 0));
	while (str[vars->i] != vars->nail && str[vars->i])
	{
		vars->join = ft_strjoin_char(vars->tmp, str[vars->i]);
		if (!vars->join)
			return (1);
		free(vars->tmp);
		vars->tmp = vars->join;
		vars->i++;
	}
	vars->i++;
	if ((is_separator(str[vars->i]) && vars->tmp[0]))
		flag = copy_cmd(vars, 1);
	else if (str[vars->i] == '\0')
		return (is_null(vars));
	if (flag)
		return (flag);
	return (0);
}

int	adding_vars(t_ms *ms, t_vars *vars, char **str)
{
	vars->tmp2 = dollar_parse(ms, *str);
	if (!vars->tmp2)
		return (1);
	*str = vars->tmp2;
	vars->count = count_tokens(*str);
	vars->cmd = (char **)malloc(sizeof(char *) * (vars->count + 1));
	if (!vars->cmd)
		return (1);
	return (0);
}
