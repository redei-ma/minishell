NAME = minishell
CC = cc
CFLAG = -Wall -Wextra -Werror -g
VALGRIND = valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes --log-file=valgrind-log.txt
# SANITIZE = -fsanitize=address, -fsanitize=undefined

SRC =	main.c \
		settings.c \
		parsing_1.c \
		parsing_2.c \
		parsing_3.c \
		lst_cmd_1.c \
		lst_cmd_2.c \
		lst_cmd_3.c \
		manager_1.c \
		manager_2.c \
		find.c \
		ft_echo_1.c \
		ft_echo_2.c \
		ft_export_1.c \
		ft_export_2.c \
		ft_exec_1.c \
		ft_exec_2.c \
		ft_minisplit.c \
		error.c \
		utils.c \
		signal.c

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(NAME): $(LIBFT) $(SRC)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAG) $(SRC) $(LIBFT) -I$(CURDIR) -o $(NAME) -lreadline

valgrind: $(NAME)
	@echo "Using Valgrind..."
	$(VALGRIND) ./$(NAME)

# sanitize: fclean
# 	@echo "Compiling $(NAME) with Address Sanitizer..."
# 	@$(CC) $(CFLAG) $(SANITIZE) $(SRC) $(LIBFT) -I$(CURDIR) -o $(NAME) -lreadline
# 	./$(NAME) 2> sanitize_log.txt

clean:
	@echo "Removing object files..."
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet

fclean: clean
	@echo "Removing library and executables..."
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

.PHONY: all clean fclean re
.SILENT:
