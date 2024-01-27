/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:26:02 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/27 13:28:38 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>

static void	exit_code_init(t_env **env)
{
	t_env	*tmp;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
	{
		perror("Malloc");
		*env = NULL;
		return ;
	}
	tmp->name = ft_strdup("?");
	if (!tmp->name)
	{
		perror("Malloc");
		*env = NULL;
		return ;
	}
	tmp->value = ft_strdup("0");
	if (!tmp->value)
	{
		perror("Malloc");
		*env = NULL;
		return ;
	}
	tmp->next = *env;
	*env = tmp;
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	i = -1;
	env = NULL;
	while (envp[++i])
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			return (perror("Malloc"), free_env(env), NULL);
		tmp->name = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		if (!tmp->name)
			return (perror("Malloc"), free(tmp), free_env(env), NULL);
		tmp->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (!tmp->value)
			return (perror("Malloc"), free_env(tmp), free_env(env), NULL);
		tmp->next = env;
		env = tmp;
	}
	if (has_env(env, "OLDPWD"))
		remove_env(&env, "OLDPWD");
	return (exit_code_init(&env), env);
}

t_env	*env_manual_init(void)
{
	t_env	*env;
	t_env	*tmp;

	env = NULL;
	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		return (perror("Malloc"), NULL);
	tmp->name = ft_strdup("PWD");
	if (!tmp->name)
		return (perror("Malloc"), free(tmp), NULL);
	tmp->value = getcwd(NULL, 0);
	if (!tmp->value)
		return (perror("Malloc"), free(tmp->name), free(tmp), NULL);
	return (tmp->next = env, env = tmp, exit_code_init(&env), env);
}

void	ms_init(t_ms *ms, char **envp)
{
	ms->cmd = NULL;
	ms->path = NULL;
	ms->path_cmd = NULL;
	ms->path_tmp = NULL;
	ms->pipe = NULL;
	ms->envp = envp;
	ms->status = 0;
	ms->redir = NULL;
	ms->flag = 0;
	if (envp[0] != 0)
	{
		ms->env = env_init(envp);
		ms->export = env_init(envp);
	}
	else
	{
		ms->env = env_manual_init();
		ms->export = env_manual_init();
	}
	if (!ms->env || !ms->export)
	{
		printf("minishell: env not imported\n");
		exit(1);
	}
}
