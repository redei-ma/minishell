NAME = minishell
CC = cc
CFLAG = -Wall -Wextra -Werror -g
VALGRIND = valgrind --suppressions=$(CURDIR)/readline.supp --leak-check=full --show-leak-kinds=all \
			--track-origins=yes --track-fds=yes --trace-children=yes #--log-file=valgrind-log.txt

SRC =	src/main.c \
		src/parser/ft_minisplit.c \
		src/parser/parsing_1.c \
		src/parser/parsing_2.c \
		src/parser/parsing_3.c \
		src/parser/parsing_4.c \
		src/interpreter/expander_1.c \
		src/interpreter/expander_2.c \
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
		src/utils/utils_2.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
# OBJDIR = .obj
# OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

# $(OBJDIR)/%.o: %.c $(LIBFT)
# 	@mkdir -p $(@D)
# 	@$(CC) $(CFLAG) -I$(CURDIR) -I$(LIBFT_DIR) -c $< -o $@

$(NAME): $(SRC) $(LIBFT)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAG) $(SRC) $(LIBFT) -I$(CURDIR) -o $(NAME) -lreadline

val: $(NAME)
	@echo "Using Valgrind..."
	$(VALGRIND) ./$(NAME)

clean:
	@echo "Removing object files..."
#	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet

fclean: clean
	@echo "Removing library and executables..."
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

.PHONY: all clean fclean re
.SILENT:
