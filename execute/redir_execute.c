/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:51:59 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/22 16:38:48 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <sys/wait.h>

static int	status_check(t_ms *ms, char **argv)
{
	if (ms->status == 255)
	{
		dup2(STD_IN, 0);
		dup2(STD_OUT, 1);
		ft_full_free(argv);
		return (258);
	}
	if (!argv)
	{
		dup2(STD_IN, 0);
		dup2(STD_OUT, 1);
		if (ms->status == 1)
			return (1);
		return (0);
	}
	if (!argv[0] || !argv[0][0] || ms->status == 1)
	{
		dup2(STD_IN, 0);
		dup2(STD_OUT, 1);
		ft_full_free(argv);
		if (ms->status == 1)
			return (1);
		return (0);
	}
	return (0);
}

static int	redir_execute_cont(t_ms *ms, char **argv, char *file, pid_t pid)
{
	pid = fork();
	if (pid < 0)
		fork_exit("fork");
	else if (pid == 0)
	{
		if (!file)
		{
			print_error(argv[0], CMD_ERROR);
			exit(127);
		}
		execve(file, argv, ms->envp);
		print_error(argv[0], CMD_ERROR);
		exit(127);
	}
	else
	{
		waitpid(pid, &ms->status, 0);
		dup2(STD_IN, 0);
		dup2(STD_OUT, 1);
		ft_full_free(argv);
		free(file);
	}
	return (ms->status / 256);
}

int	redir_execute(t_ms *ms, char *cmd)
{
	pid_t	pid;
	char	**argv;
	char	*file;
	int		ret;

	pid = 0;
	ms->status = 0;
	argv = redir_exe(ms, cmd);
	ret = status_check(ms, argv);
	if (ret == 258 || ret == 1 || !argv || !argv[0] || !argv[0][0])
		return (ret);
	file = find_path(ms, argv[0]);
	ms->status = built_in(argv, ms);
	if (ms->status != -1)
	{
		dup2(STD_IN, 0);
		dup2(STD_OUT, 1);
		ft_full_free(argv);
		free(file);
		return (ms->status);
	}
	return (redir_execute_cont(ms, argv, file, pid));
}
