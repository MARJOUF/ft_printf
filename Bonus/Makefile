NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
CRS = ft_ato_bonus.c ft_format_bonus.c ft_itoa.c\
	ft_printf_bonus.c ft_putchar.c ft_putstr.c\
	ft_read_flags.c ft_read_format.c

OBJ = $(CRS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c ft_printf_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean