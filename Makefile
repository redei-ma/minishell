NAME = minishell
CC = cc
CFLAG = -Wall -Wextra -Werror -g
VALGRIND = valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-log.txt

SRC =	main.c \
		builtin.c \
		ft_minisplit.c \
		lst_cmd_1.c \
		lst_cmd_2.c \
		utils1.c \

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(NAME): $(LIBFT) $(SRC)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAG) $(SRC) $(LIBFT) -I$(CURDIR) -o $(NAME) -lreadline

valgrind: $(LIBFT) $(SRC)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAG) $(SRC) $(LIBFT) -I$(CURDIR) -o $(NAME) -lreadline
	$(VALGRIND) ./$(NAME)

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
