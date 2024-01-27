/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:52:06 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/27 14:18:17 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	clean_ms(t_ms *ms, int flag)
{
	free_env(ms->env);
	free_env(ms->export);
	if (flag == 1)
		free_pipe(ms->pipe);
	if (flag == 2)
	{
		free_redirs(ms->redir);
		free(ms->tmp);
	}
	free(ms->line);
}

void	syntax_ctrl(char **argv, t_ms *ms)
{
	int		c;
	int		flag;
	int		flag2;

	flag2 = 0;
	flag = 0;
	c = -1;
	if (argv[1])
		argv = exit_controls(ms, argv);
	while (argv[1][++c])
	{
		if ((argv[1][c] == '-' || argv[1][c] == '+'))
			flag += 1;
		if ((flag > 1 && argv[1][c] != '-') || (flag > 1 && argv[1][c] != '+'))
			flag2 = 1;
		else if (!ft_isdigit(argv[1][c])
			&& argv[1][c] != '-' && argv[1][c] != '+')
			flag2 = 1;
		if (flag2)
		{
			print_error("exit", "numeric argument required");
			safe_exit(ms, 255, argv, 0);
		}
	}
}

void	safe_exit(t_ms *ms, int status, char **argv, int flag)
{
	if (!flag)
	{
		if (!ms->pipe->next)
		{
			ft_full_free(argv);
			clean_ms(ms, 1);
		}
		exit(status);
	}
	else if (flag == 1)
	{
		ft_putstr_fd("exit\n", 1);
		clean_ms(ms, 0);
		exit(status);
	}
	else if (flag == 2)
	{
		clean_ms(ms, 2);
		exit(status);
	}
}

int	exit_shell(char **argv, t_ms *ms)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 1)
		syntax_ctrl(argv, ms);
	if (argv[1] && ft_strlen(argv[1]) == 1
		&& (argv[1][0] == '-' || argv[1][0] == '+'))
	{
		print_error("exit", "numeric argument required");
		safe_exit(ms, 255, argv, 0);
	}
	if (i > 2)
		return (ft_putstr_fd("exit\nminishell:\
exit: too many arguments\n", 2), 1);
	if (i == 1)
		safe_exit(ms, ms->status, argv, 0);
	else if (i == 2)
	{
		ft_putstr_fd("exit\n", 1);
		safe_exit(ms, ft_atoi(argv[1]), argv, 0);
	}
	return (0);
}
