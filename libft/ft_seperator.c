/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_seperator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:41:04 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/22 18:03:01 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*redir_spc(char *tmp, int *j, char sep)
{
	char	*new;

	new = NULL;
	if (tmp[*j] && tmp[*j + 1] && tmp[*j + 1] == sep)
	{
		new = ft_roundspc(tmp, *j, ' ');
		free(tmp);
		if (!new)
			return (NULL);
		(*j) += 2;
		tmp = ft_roundspc(new, *j + 1, ' ');
		if (!tmp)
			return (free(new), NULL);
		(*j)++;
		return (free(new), tmp);
	}
	else
	{
		new = ft_roundspc(tmp, *j, ' ');
		(*j) += 2;
		free(tmp);
		tmp = ft_roundspc(new, *j, ' ');
		(*j)++;
	}
	return (free(new), tmp);
}

static char	*redir_sep(char	*tmp, int *j, int quate)
{
	char	*new;

	new = NULL;
	if (tmp && tmp[*j] && tmp[*j] == '<' && !quate)
		new = redir_spc(tmp, j, '<');
	else if (tmp && tmp[*j] && tmp[*j] == '>' && !quate)
		new = redir_spc(tmp, j, '>');
	else
		return (tmp);
	return (new);
}

char	*ft_seperator(char *cmd)
{
	int		j;
	int		quate;
	char	*tmp;

	tmp = ft_strdup(cmd);
	if (!tmp)
		return (NULL);
	free(cmd);
	quate = 0;
	j = 0;
	while (tmp[j])
	{
		if (tmp[j] && (tmp[j] == '\'' || tmp[j] == '\"'))
		{
			if (!quate)
				quate = tmp[j];
			else if (quate == tmp[j])
				quate = 0;
		}
		tmp = redir_sep(tmp, &j, quate);
		if (!tmp[j])
			break ;
		j++;
	}
	return (tmp);
}
