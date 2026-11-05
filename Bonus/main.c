#include "ft_printf_bonus.h"


int main()
{
    int i;
    i = 0;
    i = ft_printf_bonus("%-05d\n", 42);
    printf("\nresult ; %d\n", i);
    // printf("%-+010.5d", 42);
}