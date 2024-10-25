#include "./header/ft_malloc.h"

int	main() {
    for(int i = 0; i < 10000; i++) {
        ft_malloc(4097);
    }
    ft_malloc(1000000);
    ft_malloc(1000000);
    show_alloc_mem();
}