NAME = minishell
CC = cc
CFLAG = -Wall -Wextra -Werror -g
VALGRIND = valgrind --suppressions=$(CURDIR)/readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes #--log-file=valgrind-log.txt
# SANITIZE = -fsanitize=address, -fsanitize=undefined

SRC =	main.c \
		parser/parsing_1.c \
		parser/parsing_2.c \
		parser/parsing_3.c \
		parser/ft_minisplit.c \
		interpreter/lst_cmd_1.c \
		interpreter/lst_cmd_2.c \
		interpreter/lst_cmd_3.c \
		interpreter/expander.c \
		executor/manager_1.c \
		executor/manager_2.c \
		executor/ft_echo_1.c \
		executor/ft_export_1.c \
		executor/ft_export_2.c \
		executor/ft_exec_1.c \
		executor/ft_exec_2.c \
		utils/signal.c \
		utils/error.c \
		utils/utils.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(OBJDIR)/%.o: %.c $(LIBFT)
	@mkdir -p $(@D)
	@$(CC) $(CFLAG) -I$(CURDIR) -I$(LIBFT_DIR) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAG) $(OBJ) $(LIBFT) -I$(CURDIR) -o $(NAME) -lreadline

val: $(NAME)
	@echo "Using Valgrind..."
	$(VALGRIND) ./$(NAME)

# sanitize: fclean
# 	@echo "Compiling $(NAME) with Address Sanitizer..."
# 	@$(CC) $(CFLAG) $(SANITIZE) $(SRC) $(LIBFT) -I$(CURDIR) -o $(NAME) -lreadline
# 	./$(NAME) 2> sanitize_log.txt

clean:
	@echo "Removing object files..."
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet

fclean: clean
	@echo "Removing library and executables..."
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

.PHONY: all clean fclean re
.SILENT:
