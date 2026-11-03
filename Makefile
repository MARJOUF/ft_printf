NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
CRS = Mandatory/ft_printf.c Mandatory/ft_base.c Mandatory/ft_format_handel.c \
	Mandatory/ft_itoa.c Mandatory/ft_itoaf.c \
	Mandatory/ft_putchar.c Mandatory/ft_putstr.c \
	Mandatory/ft_strlen.c
OBJ = $(CRS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
