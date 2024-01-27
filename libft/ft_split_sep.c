/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:54:00 by bkas              #+#    #+#             */
/*   Updated: 2024/01/15 18:05:50 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charcount2(const char *s, char c, int *in_quotes)
{
	int	count;

	count = 0;
	while (*s && (*s != c || *in_quotes))
	{
		if (*s == '\"' || *s == '\'')
			*in_quotes = !(*in_quotes);
		else if (*s == c && !(*in_quotes))
		{
			if (*(s + 1) == c || *(s + 1) == '\0')
				break ;
		}
		count++;
		s++;
	}
	return (count);
}

static int	ft_strcount2(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	count = 1;
	while (s[i])
	{
		if (s[i + 1] != '\0' && s[i] == c && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

void	ft_free_and_return2(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	ft_fill_token2(char **ptr, int x, const char **s, char c)
{
	int	y;
	int	in_quotes;

	in_quotes = 0;
	y = 0;
	ptr[x] = (char *)malloc(sizeof(char)
			* (ft_charcount2(*s, c, &in_quotes) + 1));
	if (!ptr[x])
		ft_free_and_return2(ptr);
	while (**s && (**s != c || in_quotes))
	{
		if (**s == '\"' || **s == '\'')
			in_quotes = !in_quotes;
		else if (ft_is_end_of_token(s, c, in_quotes))
			break ;
		if (**s != '\0')
			ptr[x][y++] = *(*s)++;
	}
	if (y == 0)
	{
		ptr[x] = NULL;
		free(ptr);
	}
	ptr[x][y] = '\0';
}

char	**ft_split_sep(const char *s, char c)
{
	char	**ptr;
	int		x;

	ptr = (char **)ft_calloc(sizeof(char *), (ft_strcount2(s, c) + 1));
	if (!ptr)
		return (NULL);
	x = -1;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			ft_fill_token2(ptr, ++x, &s, c);
	}
	if (x == -1)
	{
		ptr[0] = NULL;
		free(ptr);
		return (NULL);
	}
	ptr[++x] = NULL;
	return (ptr);
}
