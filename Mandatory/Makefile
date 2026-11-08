NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADER = ft_printf.h
CRS = ft_printf.c ft_base.c ft_format_handel.c \
	ft_itoa.c ft_itoaf.c \
	ft_putchar.c ft_putstr.c \
	ft_strlen.c

OBJ = $(CRS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
