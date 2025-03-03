NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
READFLAG = -lhistory -lreadline

SRC =	main.c \
		utils1.c

OBJS = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(NAME): $(LIBFT) $(OBJS)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(READFLAG) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(CURDIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@echo "Removing object files..."
	@rm -rf $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet

fclean: clean
	@echo "Removing library and executables..."
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

.PHONY: all clean fclean re
.SILENT:
