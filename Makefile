NAME	= 	minishell

CC 		= 	gcc
CFLAGS	= 	-Wall -Wextra -Werror
RM		= 	rm -f
LDFLAGS = 	-lreadline -lhistory

LIBDIR	= 	./libft
LIB 	= 	./libft/libft.a

GREEN 	= 	\033[1;32m
RESET 	= 	\033[0m

SRC		= 	execute/add_pipes.c\
			execute/pipe_not_redir.c\
			execute/exec_utils.c\
			execute/execute_command.c\
			execute/next_process.c\
			execute/redir_execute.c\
			built-in/built-in.c\
			built-in/cd.c\
			built-in/echo.c\
			built-in/env.c\
			built-in/exit.c\
			built-in/exit_controls.c\
			built-in/export.c\
			built-in/print_export.c\
			built-in/pwd.c\
			built-in/unset.c\
			init_and_find_path/find_env.c\
			init_and_find_path/find_path.c\
			init_and_find_path/ms_init.c\
			redirections/redir_order.c\
			redirections/redir_utils.c\
			redirections/redir_run.c\
			redirections/redir_set.c\
			redirections/redir_heredoc.c\
			syntax/add_cmd_cont.c\
			syntax/add_cmd.c\
			syntax/dollar_parse_cont.c\
			syntax/dollar_parse.c\
			syntax/quate_parse.c\
			main.c

OBJS	= 	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBDIR)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIB)
	@echo "\n\n\033[1;32mMiniShell Objects Compiled \033[0m\n\n"

%.o: %.c
	@echo "$(GREEN)Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@make fclean -C $(LIBDIR)
	@echo "\n\n\033[1;31mMiniShell Objects Deleted\033[0m\n\n";

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
