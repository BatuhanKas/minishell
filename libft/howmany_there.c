/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   howmany_there.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:49:38 by melihyil          #+#    #+#             */
/*   Updated: 2023/10/30 12:51:57 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	howmany_there(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count += 1;
		i++;
	}
	return (count);
}
