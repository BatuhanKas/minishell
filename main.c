/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:46:58 by bkas              #+#    #+#             */
/*   Updated: 2024/01/27 12:29:14 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "./libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define GREEN "\033[0;32m"
#define RESET "\033[0m"

void	signal_handler(int sig)
{
	if (g_signal == 0)
	{
		if (sig == SIGINT)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (sig == SIGQUIT)
		{
		}
	}
	else if (g_signal == 1)
	{
		if (sig == SIGINT)
			g_signal = 130;
		if (sig == SIGQUIT)
			g_signal = 131;
	}
	else if (g_signal == 15 && sig == SIGINT)
	{
		printf("\n");
		exit(1);
	}
}

int	redir_syntax_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			i++;
			if (line[i] == '<' || line[i] == '>')
				i++;
			while (is_space(line[i]))
				i++;
			if (!line[i] || line[i] == '|')
			{
				if (line[i] == '|')
					return (printf("minishell: syntax \
error near unexpected token `|'\n"), 0);
				return (1);
			}
		}
		i++;
	}
	return (1);
}

int	nails_check(char *line)
{
	int	i;
	int	single;
	int	doubleq;

	i = 0;
	single = 0;
	doubleq = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !doubleq)
			single = !single;
		if (line[i] == '"' && !single)
			doubleq = !doubleq;
		i++;
	}
	if (single || doubleq)
		return (printf("minishell: syntax error\n"), 0);
	return (1);
}

void	ms_loop(t_ms *ms)
{
	while (1)
	{
		g_signal = 0;
		ms->line = readline(GREEN "MiniShell$ " RESET);
		add_history(ms->line);
		if (!ms->line)
			safe_exit(ms, 0, NULL, 1);
		g_signal = 1;
		if (ft_strlen(ms->line))
		{
			if (nails_check(ms->line) == 1 && redir_syntax_check(ms->line) == 1)
			{
				ms->cmd = ft_split_pipe(ms->line, '|');
				if (ms->cmd && add_pipes(ms) == 1)
					free_pipe(ms->pipe);
				else if (!ms->cmd && !full_space_control(ms->line))
					ms->status = 258;
			}
			else
				ms->status = 258;
			update_exit_code(ms);
		}
		free(ms->line);
	}
}

int	main(int argc, char	**argv, char **envp)
{
	t_ms	ms;

	(void)argc;
	(void)argv;
	dup2(0, STD_IN);
	dup2(1, STD_OUT);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	ms_init(&ms, envp);
	ms_loop(&ms);
	return (0);
}
