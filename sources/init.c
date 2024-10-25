#include "./../header/ft_malloc.h"

extern t_map alloc_map;

t_chunk	*get_alloc(long int psize) {
	void *allocation = mmap(NULL, psize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	t_chunk *chunk = allocation;

	chunk->allocable = true;
	chunk->size = psize - sizeof(t_chunk);
	chunk->next = NULL;

	return (chunk);
}

t_chunk	*get_tiny() {
	long int psize = sysconf(_SC_PAGE_SIZE);
	t_chunk *alloc = get_alloc(psize * 400);

	return (alloc);
}

t_chunk	*get_small() {
	long int psize = sysconf(_SC_PAGE_SIZE);
	t_chunk *alloc = get_alloc(psize * 4 * 200);

	return (alloc);
}

void	init_malloc() {
	alloc_map.tiny = get_tiny();
	alloc_map.small = get_small();
	alloc_map.large = NULL;
}