/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:32:15 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/23 11:50:31 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

void	redir_in(t_redir *redir, t_ms *ms)
{
	int		fd;

	if (redir_check(redir, ms))
	{
		ms->status = 255;
		if (ms->built_in)
			return ;
		exit(ms->status);
	}
	if (!ft_strcmp(redir->type, "<<"))
		redir_heredoc(redir, ms);
	else
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
		{
			print_error(redir->file, strerror(errno));
			if (!ms->built_in)
				exit(1);
			ms->status = 1;
			return ;
		}
		dup2(fd, 0);
		close(fd);
	}
}

void	redir_out(t_redir *redir, t_ms *ms)
{
	int	fd;

	if (redir_check(redir, ms))
	{
		ms->status = 255;
		if (ms->built_in)
			return ;
		exit(ms->status);
	}
	if (!ft_strcmp(redir->type, ">>"))
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(redir->file, strerror(errno));
		if (!ms->built_in)
			exit(1);
		ms->status = 1;
		return ;
	}
	dup2(fd, 1);
	close(fd);
}

void	redir_order(t_redirs *redir, t_ms *ms)
{
	t_redir	*tmp;

	tmp = redir->input;
	while (tmp)
	{
		redir_in(tmp, ms);
		if (ms->status != 0)
			return ;
		tmp = tmp->next;
	}
	tmp = redir->output;
	while (tmp)
	{
		redir_out(tmp, ms);
		if (ms->status != 0)
			return ;
		tmp = tmp->next;
	}
}
