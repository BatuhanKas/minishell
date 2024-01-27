/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:16:52 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/27 14:01:35 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>

#define READ_END    0
#define WRITE_END   1

void	wait_child(t_pipe *process, t_ms *ms)
{
	waitpid(process->pid, &ms->status2, 0);
	free(process->file);
}

void	wait_process(t_pipe *process)
{
	close(process->fd[WRITE_END]);
	close(process->fd[READ_END]);
	waitpid(process->pid, &process->status, 0);
	free(process->file);
	waitpid(process->next->pid, &process->next->status, 0);
	free(process->next->file);
}

void	execute(char *file, char **argv, char **envp, t_ms *ms)
{
	int	ret;

	ret = built_in(argv, ms);
	if (ret != -1)
		exit(ret);
	if (!file)
	{
		print_error(argv[0], CMD_ERROR);
		exit(127);
	}
	execve(file, argv, envp);
	print_error(argv[0], CMD_ERROR);
	exit(127);
}

void	sequential_pipe(t_pipe *process, char **envp, t_ms *ms)
{
	if (process->next == NULL)
	{
		process->pid = fork();
		if (process->pid == 0)
			child_pipe(process, envp, ms);
		else if (process->pid > 0)
			wait_child(process, ms);
		else
			fork_exit("fork");
	}
	else
		next_process(process, envp, ms);
	sequential_pipe_exit(process, ms);
}

void	next_process(t_pipe *process, char **envp, t_ms *ms)
{
	if (is_heredoc(process->cmd))
		ms->flag = 1;
	if (pipe(process->fd) == -1)
		fork_exit("pipe");
	process->pid = fork();
	if (process->pid == 0)
		next_child(process, envp, ms);
	else if (process->pid > 0)
		next_parent(process, envp, ms);
	else
		fork_exit("fork");
}
