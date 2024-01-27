/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quate_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:17:46 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/22 18:17:22 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	count_tokens_continue(const char *str, int *i, int *k, char quate)
{
	quate = str[*i];
	(*i)++;
	while (str[*i] != quate && str[*i])
		(*i)++;
	(*i)++;
	if (is_separator(str[*i]))
	{
		(*k)++;
		(*i)++;
	}
	else if (str[*i] == '\0')
	{
		(*k)++;
		return (1);
	}
	return (0);
}

int	count_tokens(const char *str)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (is_separator(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		if ((is_quote(str[i])) && (count_tokens_continue(str, &i, &k, str[i])))
			break ;
		else if (!is_quote(str[i]))
		{
			while (!is_separator(str[i]) && !is_quote(str[i]) && str[i])
				i++;
			if (is_separator(str[i]))
				k++;
			else if (str[i] == '\0')
				k++;
		}
	}
	return (k);
}

char	**add_cmd(char *str, t_ms *ms)
{
	t_vars	vars;

	init_vars(&vars, 0);
	if (adding_vars(ms, &vars, &str))
		return (perror("malloc"), NULL);
	while (str[vars.i])
	{
		if (is_full_sep(&vars, str))
			break ;
		if (is_quote(str[vars.i]))
			vars.c = in_nail(&vars, str);
		else
			vars.c = is_not_nail(&vars, str);
		if (vars.c == 1)
			return (perror("malloc"), NULL);
		else if (vars.c == 2)
			break ;
	}
	add_null(&vars);
	return (vars.cmd);
}
