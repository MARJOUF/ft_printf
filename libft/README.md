*This project has been created as part of the 42 curriculum by akmarjou.*

# Libft

## Description

Libft is my first project at 42. The goal is to build my own C library (`libft.a`) with re-coded libc functions and some extra utility functions that I will reuse in the next projects.

The library has three parts:

- **Libc functions**: `ft_strlen`, `ft_memcpy`, `ft_memmove`, `ft_strlcpy`, `ft_strlcat`, `ft_strncmp`, `ft_strnstr`, `ft_atoi`, `ft_calloc`, `ft_strdup`, `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`, `ft_toupper`, `ft_tolower`, `ft_memset`, `ft_bzero`, `ft_memchr`, `ft_memcmp`, `ft_strchr`, `ft_strrchr`.
- **Additional functions**: `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`, `ft_strmapi`, `ft_striteri`, `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`.
- **Linked lists** (`t_list`): `ft_lstnew`, `ft_lstadd_front`, `ft_lstadd_back`, `ft_lstsize`, `ft_lstlast`, `ft_lstdelone`, `ft_lstclear`, `ft_lstiter`, `ft_lstmap`.

Notes: `ft_memmove` handles overlapping memory. `ft_split` frees everything if a `malloc` fails.

## Instructions

```bash
make          # build libft.a
make clean    # remove object files
make fclean   # remove object files and libft.a
make re       # rebuild everything
```

To use it in a program:

```c
#include "libft.h"
```

```bash
cc main.c -L. -lft -o my_program
```

## Resources

- [Linux man pages](https://man7.org/linux/man-pages/)
- [cppreference (C)](https://en.cppreference.com/w/c)
- [GNU Make manual](https://www.gnu.org/software/make/manual/make.html)
- [The 42 Norm](https://elearning.intra.42.fr/notions/the-norm/subnotions/norm-v4/pdfs/Norm%20V4)

**AI usage:** I used Claude to review my code and to explain some bugs and edge cases (`ft_strncmp`, `ft_isalpha`, overflow in `ft_atoi`).I wrote the functions myself and tested every change before keeping it.
