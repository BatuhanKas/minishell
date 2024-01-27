/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:21:50 by bkas              #+#    #+#             */
/*   Updated: 2024/01/19 10:15:27 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>

void	fork_exit(char *str)
{
	perror(str);
	exit(1);
}

void	print_error(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(error, STDERR_FILENO);
}

void	free_pipe(t_pipe *pipe)
{
	t_pipe	*tmp;

	if (!pipe)
		return ;
	while (pipe)
	{
		tmp = pipe;
		pipe = pipe->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->file)
			free(tmp->file);
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
	tmp = NULL;
}

int	is_redir(char *str)
{
	int	i;
	int	quote_count;

	i = 0;
	while (str[i])
	{
		quote_count = 0;
		while (str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
				quote_count++;
			i++;
		}
		if (quote_count % 2 == 0
			&& (ft_strchr(str, '>') || ft_strchr(str, '<')))
			return (1);
	}
	return (0);
}

void	sequential_pipe_exit(t_pipe *process, t_ms *ms)
{
	if (process->next == NULL)
	{
		if (ms->status2 == 2)
			exit(130);
		else if (ms->status2 == 3)
			exit(131);
		exit(ms->status2 >> 8);
	}
	else
		exit(process->next->status >> 8);
}
