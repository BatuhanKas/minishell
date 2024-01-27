/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:40:35 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/23 11:11:01 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

static char	*quate_parse(char *str)
{
	int		i;
	int		j;
	char	*new;
	char	quate;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (perror("Malloc"), NULL);
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quate = str[i++];
			while (str[i] && str[i] != quate)
				new[j++] = str[i++];
			i++;
		}
		else
			new[j++] = str[i++];
	}
	return (new[j] = '\0', new);
}

void	redir_init_l(t_redirs *redir, char **command, int *i)
{
	t_redir	*tmp;

	if (!redir->input)
	{
		redir->input = malloc(sizeof(t_redir));
		if (!redir->input)
			return (perror("Malloc"));
		redir->input->type = command[*i];
		redir->input->file = quate_parse(command[++(*i)]);
		free(command[*i]);
		command[*i] = redir->input->file;
		redir->input->next = NULL;
		return ;
	}
	tmp = redir->input;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_redir));
	if (!tmp->next)
		return (perror("Malloc"));
	tmp->next->type = command[*i];
	tmp->next->file = quate_parse(command[++(*i)]);
	free(command[*i]);
	command[*i] = tmp->next->file;
	tmp->next->next = NULL;
}

void	redir_init_r(t_redirs	*redir, char **command, int *i)
{
	t_redir	*tmp;

	if (!redir->output)
	{
		redir->output = malloc(sizeof(t_redir));
		if (!redir->output)
			return (perror("Malloc"));
		redir->output->type = command[*i];
		redir->output->file = quate_parse(command[++(*i)]);
		free(command[*i]);
		command[*i] = redir->output->file;
		redir->output->next = NULL;
		return ;
	}
	tmp = redir->output;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_redir));
	if (!tmp->next)
		return (perror("Malloc"));
	tmp->next->type = command[*i];
	tmp->next->file = quate_parse(command[++(*i)]);
	free(command[*i]);
	command[*i] = tmp->next->file;
	tmp->next->next = NULL;
}

void	redir_none(t_redirs	*redir, char **command, int *i)
{
	t_redir	*tmp;

	if (!redir->cmd)
	{
		redir->cmd = malloc(sizeof(t_redir));
		if (!redir->cmd)
			return (perror("Malloc"));
		redir->cmd->type = command[*i];
		redir->cmd->next = NULL;
		return ;
	}
	tmp = redir->cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_redir));
	if (!tmp->next)
		return (perror("Malloc"));
	tmp->next->type = command[*i];
	tmp->next->next = NULL;
}

void	redir_add(t_redirs	*redir, char **command, int *i)
{
	if (!ft_strcmp(command[*i], "<") || !ft_strcmp(command[*i], "<<"))
		redir_init_l(redir, command, i);
	else if (!ft_strcmp(command[*i], ">") || !ft_strcmp(command[*i], ">>"))
		redir_init_r(redir, command, i);
	else
		redir_none(redir, command, i);
}
