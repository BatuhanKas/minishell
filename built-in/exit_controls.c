/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:48:52 by batuhan           #+#    #+#             */
/*   Updated: 2024/01/27 12:26:29 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	**exit_controls(t_ms *ms, char **argv)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (argv[1][i] || argv[1][i] == '\0')
	{
		while (is_space(argv[1][i]))
			i++;
		if (argv[1][i] == '\0')
		{
			print_error("exit", "numeric argument required");
			safe_exit(ms, 255, argv, 0);
		}
	}
	tmp = ft_strtrim(argv[1], " /t/n");
	if (!tmp)
		safe_exit(ms, 255, argv, 0);
	free(argv[1]);
	argv[1] = tmp;
	return (argv);
}
