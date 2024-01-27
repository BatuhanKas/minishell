# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 19:59:35 by melihyil          #+#    #+#              #
#    Updated: 2024/01/08 16:28:23 by bkas             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= libft.a

CC 			= gcc

CFLAGS 		= -Wall -Werror -Wextra

REMOVE 		= rm -f

INCLUDE = -I ./

SRCS 		= ft_isalpha.c 	\
			ft_strnew.c		\
			ft_strclr.c		\
			ft_strncpy.c	\
			ft_isdigit.c 	\
			ft_isalnum.c 	\
			ft_isnum.c 	\
			ft_isascii.c 	\
			ft_isprint.c 	\
			ft_strlen.c 	\
			ft_memset.c 	\
			ft_bzero.c 		\
			ft_memcpy.c 	\
			ft_memmove.c 	\
			ft_strlcpy.c 	\
			ft_strlcat.c 	\
			ft_toupper.c 	\
			ft_tolower.c 	\
			ft_strchr.c 	\
			ft_strcmp.c		\
			ft_strrchr.c 	\
			ft_strncmp.c	\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_strnstr.c	\
			ft_atoi.c 		\
			ft_atol.c 		\
			ft_strdup.c 	\
			ft_calloc.c 	\
			ft_itoa.c 		\
			ft_substr.c	 	\
			ft_split.c 		\
			ft_strjoin.c 	\
			ft_strstr.c		\
			ft_strtrim.c	\
			ft_itoa.c 		\
			ft_strmapi.c 	\
			ft_striteri.c 	\
			get_next_line.c	\
			ft_putstr_fd.c 	\
			ft_putchar_fd.c \
			ft_putstr_fd.c 	\
			ft_putendl_fd.c \
			ft_putnbr_fd.c	\
			ft_mapnamecontrol.c \
			get_next_line.c \
			free_stash.c \
			howmany_there.c\
			ft_free.c\
			ft_strtok.c\
			ft_whitespace.c\
			ft_roundspc.c\
			ft_strjoin_char.c\
			is_space.c\
			ft_seperator.c\
			ft_check_pipe.c\
			ft_split_sep.c\
			ft_pipe_control.c\
			ft_end_token.c\
			ft_free_and_return.c\
			ft_split_pipe.c\
			pipe_controls.c

BONUS_SRCS	= ft_lstnew.c		\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c

PRINTF_SRCS = ./ft_printf/ft_printf.c \
	./ft_printf/ft_print_char.c \
	./ft_printf/ft_print_ptr.c	\
	./ft_printf/ft_print_str.c	\
	./ft_printf/ft_print_int.c	\
	./ft_printf/ft_print_hex.c	\
	./ft_printf/ft_print_unsint.c

OBJS 		= $(SRCS:.c=.o)

BONUS_OBJS 	= $(BONUS_SRCS:.c=.o)
PRINTF_OBJ = $(PRINTF_SRCS:.c=.o)

all:		$(NAME)

$(NAME): 	$(OBJS) $(PRINTF_OBJ)
			@ar -rcs $(NAME) $(OBJS) $(PRINTF_OBJ)

bonus:		$(NAME) $(BONUS_OBJS)
			@ar -rcs $(NAME) $(BONUS_OBJS)

.c.o:
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
			@$(REMOVE) $(OBJS) $(BONUS_OBJS) $(PRINTF_OBJ)

fclean:		clean
			@$(REMOVE) $(NAME)

re:			fclean $(NAME)

rebonus:	fclean bonus

.PHONY:		all clean fclean re bonus rebonus printf
