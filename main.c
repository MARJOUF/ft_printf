int ft_printf(const char *str, ...);
#include <stdio.h>
#include <unistd.h>
int main()
{
    char a = 'a';
    char *b = "akram454 45345 hello sdsdasd dasdas";
    int l = 234;
    char j = 110;
    char *d = &j;
    int count;
    int k = 1;
    unsigned int o = -20;
    unsigned int n = 20;
    // close(1);
    setvbuf(stdout, NULL, _IONBF, 0);
    count = printf("%s %c %d %p %i %u %x %X \n",b, a, l, d, k, o, n, n);
    printf("%d\n", count);
    dprintf(2, "%d\n", count);
    printf("\n");
    count = ft_printf("%s %c %d %p %i %u %x %X \n",b, a, l, d, k, o, n, n);
    printf("%d\n", count);
    dprintf(2, "%d\n", count);
    return 0;
}