NAME = minishell
CC = cc
CFLAG = -Wall -Wextra -Werror -g
VALGRIND = valgrind --suppressions=$(SUP_FILE_ABS) --leak-check=full --show-leak-kinds=all \
			--track-origins=yes --track-fds=yes --trace-children=yes

SRC =	src/main.c \
		src/parser/ft_minisplit.c \
		src/parser/parsing_1.c \
		src/parser/parsing_2.c \
		src/parser/parsing_3.c \
		src/parser/parsing_4.c \
		src/interpreter/expander_1.c \
		src/interpreter/expander_2.c \
		src/interpreter/expander_3.c \
		src/interpreter/expander_hd.c \
		src/interpreter/lst_cmd_1.c \
		src/interpreter/lst_cmd_2.c \
		src/interpreter/lst_cmd_3.c \
		src/executor/ft_builtin.c \
		src/executor/ft_cd.c \
		src/executor/ft_echo_1.c \
		src/executor/ft_exec_1.c \
		src/executor/ft_exec_2.c \
		src/executor/ft_export_1.c \
		src/executor/ft_export_2.c \
		src/executor/ft_export_3.c \
		src/executor/manager_1.c \
		src/executor/manager_2.c \
		src/utils/error_1.c \
		src/utils/error_2.c \
		src/utils/signal_1.c \
		src/utils/signal_2.c \
		src/utils/utils_1.c \
		src/utils/utils_2.c \
		src/utils/utils_3.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
SUP_FILE = suppression/readline.supp
SUP_FILE_ABS = $(shell pwd)/$(SUP_FILE)
OBJ_DIR = .obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(OBJ_DIR)/%.o: %.c $(LIBFT)
	@mkdir -p $(@D)
	@$(CC) $(CFLAG) -Iinclude -I$(LIBFT_DIR) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAG) $(OBJ) $(LIBFT) -Iinclude -o $(NAME) -lreadline

banner: $(NAME)
	@clear
	@sleep 0.1;echo "\033[1;97m"
	@sleep 0.1;echo "███╗   ███╗██╗███╗   ██╗██ ██╗  ██╗███████╗██╗     ██╗     "
	@sleep 0.1;echo "████╗ ████║██║████╗  ██║██║██║  ██║██╔════╝██║     ██║     "
	@sleep 0.1;echo "██╔████╔██║██║██╔██╗ ██║██║███████║█████╗  ██║     ██║     "
	@sleep 0.1;echo "██║╚██╔╝██║██║██║╚██╗██║██║██╔══██║██╔══╝  ██║     ██║     "
	@sleep 0.1;echo "██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║███████╗███████╗███████╗"
	@sleep 0.1;echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "\033[0m"
	@./$(NAME)

val: $(NAME) $(SUP_FILE)
	@echo "Using Valgrind..."
	@$(VALGRIND) ./$(NAME)

clean:
	@echo "Removing object files..."
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet

fclean: clean
	@echo "Removing library and executables..."
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet
	@rm -rf $(SUP_FILE_DIR)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
