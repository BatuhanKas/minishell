/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_not_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:24:18 by bkas              #+#    #+#             */
/*   Updated: 2024/01/27 14:19:29 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <sys/wait.h>

int	not_redir(t_ms *ms, char **cmd, pid_t pid)
{
	cmd = add_cmd(ms->pipe->cmd, ms);
	if (!cmd)
		return (1);
	ms->pipe->file = find_path(ms, cmd[0]);
	ms->status = built_in(cmd, ms);
	if (ms->status == -1)
	{
		pid = fork();
		if (pid == 0)
		{
			execute(ms->pipe->file, cmd, ms->envp, ms);
			clean_ms(ms, 0);
			free(ms->pipe->file);
			ft_full_free(cmd);
			exit(0);
		}
		else if (pid > 0)
			waitpid(pid, &ms->pipe->status, 0);
		else
			fork_exit("fork");
		ms->status = ms->pipe->status >> 8;
	}
	ft_full_free(cmd);
	return (0);
}
