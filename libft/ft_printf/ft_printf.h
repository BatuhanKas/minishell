/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:08:16 by melihyil          #+#    #+#             */
/*   Updated: 2023/09/03 16:18:54 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int		ft_printf(const char *format, ...);
int		ft_print_str(char *str);
int		ft_print_char(char c);
int		ft_print_int(int n);
int		ft_print_hex(unsigned int num, const char format);
int		ft_print_ptr(unsigned long long ptr, int i);
int		ft_print_unsint(unsigned int nb);
int		ft_printpercent(void);

#endif
