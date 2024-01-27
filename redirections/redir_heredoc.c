/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:33:33 by bkas              #+#    #+#             */
/*   Updated: 2024/01/27 11:56:56 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

static void	write_heredoc(int *fd, char *line, t_ms *ms)
{
	char	*tmp;

	g_signal = 15;
	tmp = dollar_parse(ms, line);
	free(line);
	write(fd[1], tmp, ft_strlen(tmp));
	write(fd[1], "\n", 1);
	free(tmp);
	if (g_signal == 2)
		ms->status = 1;
}

static void	write_to_heredoc(int *fd, t_ms *ms, t_redir *redir)
{
	char	*line;

	line = NULL;
	g_signal = 15;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, redir->file))
			break ;
		else
			write_heredoc(fd, line, ms);
	}
	free(line);
}

void	redir_heredoc(t_redir *redir, t_ms *ms)
{
	int		fd[2];
	int		fd2;
	int		pid;

	fd2 = dup(1);
	dup2(STD_OUT, 1);
	dup2(STD_IN, 0);
	if (pipe(fd) == -1)
		return (perror("Pipe"));
	g_signal = 2;
	pid = fork();
	if (pid == 0)
	{
		write_to_heredoc(fd, ms, redir);
		close(fd[1]);
		close(fd[0]);
		safe_exit(ms, 0, NULL, 2);
	}
	waitpid(pid, &ms->status, 0);
	g_signal = 1;
	ms->status /= 256;
	dup2(fd2, 1);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}
