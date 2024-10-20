#include "./../header/malloc.h"

void	*malloc(size_t size) {
	char *test = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}