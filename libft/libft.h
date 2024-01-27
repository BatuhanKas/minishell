/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:12:41 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/17 10:19:17 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include "./ft_printf/ft_printf.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef NUM_OF_FD
#  define NUM_OF_FD 4096
# endif

typedef struct s_variable
{
	int	left;
	int	right;
	int	in_quotes;
	int	has_command_before_pipe;
	int	has_command_after_pipe;
	int	i;
}	t_variable;

int		ft_isalpha(int c);
int		ft_strisalpha(char	*str);
int		ft_isdigit(int c);
int		ft_isnum(char *str);
int		ft_isalnum(int c);
int		ft_strisalnum(char	*str);
int		ft_isprint(int c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_isascii(int c);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
int		howmany_there(char	*str, char c);

char	**ft_split(char const *s, char c);
char	**ft_split_pipe(char const *s, char c);
char	**ft_split_sep(char const *s, char c);
int		ft_first_pipe_control(const char *tmp, char c);
int		ft_last_pipe_control(const char *tmp, char sep);
void	ft_free_and_return(char **ptr);
void	ft_fill_token(char **ptr, int x, const char **s, char c);
int		ft_is_end_of_token(const char **s, char c, int in_quotes);
char	**ft_full_free(char **tab);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_char(char *s1, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *str);
char	*ft_strtok(char *str, char *sep);
int		is_space(char c);

void	ft_bzero(void *str, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t num, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strnew(size_t size);
char	*ft_strncpy(char *dest, char *src, size_t n);
void	ft_strclr(char *s);
void	ft_free(void *str);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memmove(void *s1, const void *s2, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_mapnamecontrol(char *str, char dot);
int		ft_whitespace(char c);
char	*ft_roundspc(char *str, int index, char c);
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		get_next_line(int fd, char **str);
void	*ft_free_stash(char **stash, int create_line);
char	*ft_seperator(char *cmd);
void	init_variable(t_variable *var);
int		ft_run_pipe(const char *s, char c);
int		is_quote(char c);
int		has_valid_command(const char *s, char c, int start);
int		find_right_boundary(const char *s, char c, int position, int *boundary);
void	find_left_boundary(const char *s, char c, int position, int *boundary);
int		ft_check_pipe_syntax(const char *s, char c, t_variable *var);
int		ft_syntax_continue(const char *s, char c, t_variable *var);
int		check_space_between_pipes(const char *s, char c, int position);
int		ft_strcount(char const *s, char c);
int		ft_charcount(const char *s, char c, int *in_quotes);
int		full_space_control(const char *s);

#endif
