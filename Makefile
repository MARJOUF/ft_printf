NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
CRS = Mandatory/ft_printf.c
OBJ = $(CRS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c ft_printf.h
	cd libft $(MAKE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
