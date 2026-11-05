NAME = Bonus/libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADER = Mandatory/ft_printf.h
CRS = Mandatory/ft_printf.c Mandatory/ft_base.c Mandatory/ft_format_handel.c \
	Mandatory/ft_itoa.c Mandatory/ft_itoaf.c \
	Mandatory/ft_putchar.c Mandatory/ft_putstr.c \
	Mandatory/ft_strlen.c
CRS2 = Bonus/ft_ato_bonus.c Bonus/ft_printf_bonus.c  Bonus/ft_printf_bonus.h\
	Bonus/ft_printf_bonus.h.gch  Bonus/ft_read_flags.c  Bonus/ft_read_format.c

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
