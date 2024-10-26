#include "./header/ft_malloc.h"

int	main() {
    // for(int i = 0; i < 10000; i++) {
    //     ft_malloc(i);
    // }
    void *test1 = ft_malloc(1000001);
    void *test2 = ft_malloc(1000002);
    void *test3 = ft_malloc(1000003);
    show_alloc_mem();
    write(1, "\n\n", 2);
    ft_free(test3);
    show_alloc_mem();
}