# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/03 17:34:38 by melihyil          #+#    #+#              #
#    Updated: 2023/09/03 17:34:39 by melihyil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
SRCS =	./ft_printf.c \
	./ft_print_char.c \
	./ft_print_ptr.c	\
	./ft_print_str.c	\
	./ft_print_int.c	\
	./ft_print_hex.c	\
	./ft_print_unsint.c

OBJS = $(SRCS:.c=.o)
REMOVE = rm -f

GREEN		= \033[0;32m
GREY		= \033[0;90m
RED			= \033[0;31m
WHITE		= \033[0;37m
RESET		= \033[0m
TICK		= ✅
CROSS = ❌

all:		$(NAME)

$(NAME): 	$(OBJS)
			@ar -rcs $(NAME) $(OBJS)
			@echo "$(GREY)libftprintf: $(GREEN)$(NAME) was created $(TICK)"

.c.o:
			@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)
			@echo "$(GREY)libftprintf: $(GREEN)$< was created $(TICK)"

clean:
			@$(REMOVE) $(OBJS) $(BONUS_OBJS)
			@echo "$(RED)Printf: object files were deleted $(CROSS)"

fclean:		clean
			@$(REMOVE) $(NAME)
			@echo "$(RED)Printf: $(NAME) was deleted $(CROSS)"

re:			fclean $(NAME)


.PHONY: all re fclean clean
