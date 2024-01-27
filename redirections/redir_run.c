/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:40:28 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/23 13:04:58 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

static char	**redir_exe2(t_ms *ms, t_redirs *redir, char **tmp2)
{
	char	*tmp;

	tmp = re_create_cmd(redir->cmd);
	if (!tmp)
		return (NULL);
	ms->tmp = tmp;
	ms->redir = redir;
	redir_order(redir, ms);
	free_redirs(redir);
	if (tmp[0])
		tmp2 = add_cmd(tmp, ms);
	free(tmp);
	return (tmp2);
}

char	**redir_exe(t_ms *ms, char *argv)
{
	t_redirs	redir;
	char		**tmp2;
	char		*tmp;
	int			i;

	redir.cmd = NULL;
	redir.input = NULL;
	redir.output = NULL;
	i = -1;
	tmp2 = NULL;
	tmp = ft_seperator(argv);
	if (!tmp)
		return (NULL);
	redir.argv = ft_split_sep(tmp, ' ');
	if (!redir.argv)
		return (perror("Malloc"), NULL);
	free(tmp);
	while (redir.argv[++i])
	{
		redir_add(&redir, redir.argv, &i);
		if (!redir.argv[i])
			break ;
	}
	return (redir_exe2(ms, &redir, tmp2));
}
