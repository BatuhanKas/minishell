/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:15:08 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/23 17:23:13 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

t_pipe	*add_pipe(t_pipe *pipe, char *cmd)
{
	t_pipe	*tmp;
	t_pipe	*new;

	tmp = pipe;
	new = (t_pipe *)malloc(sizeof(t_pipe));
	if (!new)
		return (perror("malloc"), NULL);
	new->cmd = ft_strdup(cmd);
	if (!new->cmd)
		return (perror("malloc"), NULL);
	new->file = NULL;
	new->argv = NULL;
	new->status = 0;
	new->next = NULL;
	if (!pipe)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (pipe);
}

int	add_pipes(t_ms *ms)
{
	t_pipe	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	while (ms->cmd[++i])
	{
		tmp = add_pipe(tmp, ms->cmd[i]);
		if (!tmp)
			return (free_pipe(tmp), 0);
	}
	ft_full_free(ms->cmd);
	ms->cmd = NULL;
	ms->pipe = tmp;
	execute_full(ms);
	return (1);
}

void	execute_full(t_ms *ms)
{
	pid_t	pid;
	char	**cmd;

	pid = 0;
	cmd = NULL;
	ms->built_in = 0;
	if (!ms->pipe->next)
	{
		if (is_redir(ms->pipe->cmd))
		{
			ms->built_in = 1;
			ms->status = redir_execute(ms, ms->pipe->cmd);
			if (ms->status == 255)
			{
				print_error(ms->pipe->cmd, SYNTAX_ERROR3);
				ms->status = 258;
			}
			ms->pipe->cmd = 0;
		}
		else
			if (not_redir(ms, cmd, pid))
				perror("malloc");
	}
	else
		execute_full_pipe(ms);
}

void	execute_full_pipe(t_ms *ms)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		sequential_pipe(ms->pipe, ms->envp, ms);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		ms->status = status >> 8;
		if (ms->status == 255)
			ms->status = 258;
		g_signal = status;
	}
	else
		perror("fork");
}
