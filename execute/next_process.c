/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:04:32 by bkas              #+#    #+#             */
/*   Updated: 2024/01/23 18:11:39 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>

#define READ_END    0
#define WRITE_END   1

int	is_heredoc(char *argv)
{
	int	flag;
	int	quate;
	int	j;

	j = 0;
	flag = 0;
	quate = 0;
	while (argv[j])
	{
		if (argv[j] == '\'' || argv[j] == '\"')
		{
			if (!quate)
				quate = argv[j];
			else if (quate == argv[j])
				quate = 0;
			j++;
		}
		if (argv[j] && argv[j + 1]
			&& argv[j] == '<' && argv[j + 1] == '<' && !quate)
			flag = 1;
		j++;
	}
	return (flag);
}

void	child_pipe(t_pipe *process, char **envp, t_ms *ms)
{
	if (is_redir(process->cmd))
	{
		process->argv = redir_exe(ms, process->cmd);
		if (ms->status == 1)
			exit(1);
		process->file = find_path(ms, process->argv[0]);
	}
	else
	{
		process->argv = add_cmd(process->cmd, ms);
		free(process->cmd);
		process->file = find_path(ms, process->argv[0]);
	}
	execute(process->file, process->argv, envp, ms);
}

void	next_parent(t_pipe *process, char **envp, t_ms *ms)
{
	if (ms->flag == 1)
	{
		waitpid(process->pid, &process->status, 0);
		if ((process->status / 256) == 1 || (process->status / 256) == 255)
			exit(process->status / 256);
		free(process->file);
	}
	process->next->pid = fork();
	if (process->next->pid == 0)
	{
		if (is_heredoc(process->next->cmd))
			sequential_pipe(process->next, envp, ms);
		else
		{
			close(process->fd[WRITE_END]);
			dup2(process->fd[READ_END], STDIN_FILENO);
			close(process->fd[READ_END]);
			sequential_pipe(process->next, envp, ms);
		}
	}
	else if (process->next->pid > 0)
		wait_process(process);
	else
		fork_exit("fork");
}

void	next_child(t_pipe *process, char **envp, t_ms *ms)
{
	close(process->fd[READ_END]);
	dup2(process->fd[WRITE_END], STDOUT_FILENO);
	close(process->fd[WRITE_END]);
	if (is_redir(process->cmd))
	{
		process->argv = redir_exe(ms, process->cmd);
		if (ms->status == 1)
			exit(1);
		process->file = find_path(ms, process->argv[0]);
	}
	else
	{
		process->argv = add_cmd(process->cmd, ms);
		free(process->cmd);
		process->file = find_path(ms, process->argv[0]);
	}
	execute(process->file, process->argv, envp, ms);
}
