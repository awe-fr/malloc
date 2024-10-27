#include "./header/ft_malloc.h"

int	main() {
    for(int i = 0; i < 300000; i++) {
        ft_free(ft_malloc(i));
        putnbr(i);
        write(1, "\n", 1);
    }
    ft_malloc(2200);
    // void *test1 = ft_malloc(10);
    // void *test2 = ft_malloc(10);
    // void *test3 = ft_malloc(10);
    // show_alloc_mem();
    // write(1, "\n\n", 2);
    // ft_free(test1);
    // ft_free(test2);
    // ft_free(test3);
    show_alloc_mem();
}