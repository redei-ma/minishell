NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(CURDIR)

SRC = ft_abs.c \
	ft_atoi.c \
	ft_bzero.c \
	ft_freemat.c \
	ft_itoa.c \
	ft_matlen.c	\
	ft_natoi.c \
	ft_tolower.c \
	ft_toupper.c \
	get_next_line_bonus.c \
	alloc/ft_calloc.c	alloc/ft_nsplit.c	alloc/ft_realloc.c	alloc/ft_split.c	alloc/ft_strdup.c	alloc/ft_strjoin.c	alloc/ft_substr.c \
	lst/ft_lstadd_back.c	lst/ft_lstadd_front.c	lst/ft_lstclear.c	lst/ft_lstdelone.c \
	lst/ft_lstiter.c	lst/ft_lstlast.c	lst/ft_lstmap.c	lst/ft_lstnew.c	lst/ft_lstsize.c \
	mem/ft_memchr.c	mem/ft_memcmp.c	mem/ft_memcpy.c	mem/ft_memmove.c	mem/ft_memset.c \
	print/ft_printf_utils.c	print/ft_printf.c	print/ft_printfd_utils.c	print/ft_printfd.c	print/ft_putchar_fd.c	print/ft_putendl_fd.c	print/ft_putnbr_fd.c	print/ft_putstr_fd.c \
	str/ft_strchr.c	str/ft_striteri.c	str/ft_strlcat.c	str/ft_strlcpy.c	str/ft_strlen.c	str/ft_strmapi.c	str/ft_strncmp.c	str/ft_strnstr.c	str/ft_strrchr.c	str/ft_strtrim.c \
	type/ft_isalnum.c	type/ft_isalpha.c	type/ft_isascii.c	type/ft_isdigit.c	type/ft_isprint.c	type/ft_isspace.c \

OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
