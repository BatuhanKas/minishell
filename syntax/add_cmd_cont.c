/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_cont.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:37:13 by bkas              #+#    #+#             */
/*   Updated: 2024/01/15 18:10:21 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	add_null(t_vars *vars)
{
	vars->cmd[vars->k] = NULL;
	if (vars->tmp)
		free(vars->tmp);
	if (vars->tmp2)
		free(vars->tmp2);
	if (vars->cmd[0] == NULL)
	{
		free(vars->cmd);
		vars->cmd = NULL;
	}
}

int	is_full_sep(t_vars *vars, char *str)
{
	while (is_separator(str[vars->i]))
		vars->i++;
	if (str[vars->i] == '\0')
		return (1);
	return (0);
}

int	is_null_again(t_vars *vars)
{
	vars->cmd[vars->k] = ft_strdup(vars->tmp);
	if (!vars->cmd[vars->k])
		return (1);
	vars->k++;
	ft_strclr(vars->tmp);
	return (2);
}

int	is_not_nail(t_vars *vars, char *str)
{
	while (!is_separator(str[vars->i])
		&& !is_quote(str[vars->i]) && str[vars->i])
	{
		vars->join = ft_strjoin_char(vars->tmp, str[vars->i]);
		if (!vars->join)
			return (1);
		free(vars->tmp);
		vars->tmp = vars->join;
		vars->i++;
	}
	if (is_separator(str[vars->i]) && vars->tmp)
	{
		vars->cmd[vars->k] = ft_strdup(vars->tmp);
		if (!vars->cmd[vars->k])
			return (1);
		vars->k++;
		ft_strclr(vars->tmp);
	}
	else if (str[vars->i] == '\0')
		return (is_null_again(vars));
	return (0);
}
