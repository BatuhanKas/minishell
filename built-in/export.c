/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:30:59 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/27 13:37:09 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	*get_name(char	*str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		name = ft_substr(str, 0, i);
		return (name);
	}
	else
		name = ft_strdup(str);
	return (name);
}

char	*get_value(char	*str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		value = ft_substr(str, i + 1, ft_strlen(str) - i);
		return (value);
	}
	return (NULL);
}

int	export_loop(t_ms *ms, char *name, char *value)
{
	if (ft_strisalpha(name) && ft_strlen(name))
	{
		add_env(&ms->env, name, value);
		add_env(&ms->export, name, value);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(name, 2);
		if (value)
		{
			ft_putstr_fd("=", 2);
			ft_putstr_fd(value, 2);
		}
		ft_putendl_fd(": not a valid identifier", 2);
		return (1);
	}
	return (0);
}

int	export_add_loop(char **argv, t_ms *ms, int i, int flag)
{
	char	*name;
	char	*value;
	int		ret;

	while (argv[i] != NULL)
	{
		if (ft_strchr(argv[i], '='))
		{
			name = get_name(argv[i]);
			value = get_value(argv[i]);
			ret = export_loop(ms, name, value);
			if (name)
				free(name);
			if (value)
				free(value);
		}
		else
			ret = export_loop(ms, argv[i], NULL);
		if (ret == 1)
			flag = 1;
		i++;
	}
	return (flag);
}

int	export(char **argv, t_ms *ms)
{
	int		i;
	int		flag;
	int		ret;
	char	*temp_name;
	char	*temp_value;

	flag = 0;
	i = 1;
	ret = 0;
	temp_name = NULL;
	temp_value = NULL;
	if (!argv[1])
		return (sort_export(&ms->export, temp_name, temp_value));
	flag = export_add_loop(argv, ms, i, flag);
	if (flag == 1)
		ret = 1;
	return (ret);
}
