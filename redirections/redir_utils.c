/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:40:41 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/23 17:31:12 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	free_redirs(t_redirs *redir)
{
	t_redir	*tmp;

	tmp = redir->input;
	while (tmp)
	{
		redir->input = tmp->next;
		free(tmp);
		tmp = redir->input;
	}
	tmp = redir->output;
	while (tmp)
	{
		redir->output = tmp->next;
		free(tmp);
		tmp = redir->output;
	}
	tmp = redir->cmd;
	while (tmp)
	{
		redir->cmd = tmp->next;
		free(tmp);
		tmp = redir->cmd;
	}
	ft_full_free(redir->argv);
}

char	*re_create_cmd(t_redir *lst)
{
	char	*cmd;
	t_redir	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i += ft_strlen(tmp->type) + 1;
		tmp = tmp->next;
	}
	cmd = malloc(sizeof(char) * (i + 2));
	tmp = lst;
	cmd[0] = 0;
	while (tmp)
	{
		ft_strlcat(cmd, tmp->type, ft_strlen(tmp->type) + ft_strlen(cmd) + 1);
		ft_strlcat(cmd, " ", ft_strlen(cmd) + 2);
		tmp = tmp->next;
	}
	return (cmd);
}

int	redir_check(t_redir *redir, t_ms *ms)
{
	if (!redir->file)
	{
		if (ms->pipe->next)
			print_error(NULL, SYNTAX_ERROR2);
		else if (!ms->pipe->next)
			print_error(redir->type, SYNTAX_ERROR3);
		return (1);
	}
	if (!ft_strcmp(redir->file, ">>") || !ft_strcmp(redir->file, ">")
		|| !ft_strcmp(redir->file, "<") || !ft_strcmp(redir->file, "<<"))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putendl_fd("'", 2);
		return (1);
	}
	return (0);
}
