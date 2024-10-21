#include "./../header/ft_malloc.h"

extern t_map alloc_map;

t_alloc	*get_alloc(long int psize) {
	t_alloc alloc;
	t_chunk chunk;

	chunk.allocable = true;
	chunk.size = psize;
	chunk.address = mmap(NULL, psize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	chunk.next = NULL;

	alloc.count = 0;
	alloc.chunks = &chunk;
	alloc.next = NULL;

	t_alloc *ret = &alloc;

	return (ret);
}

t_alloc	*get_tiny() {
	long int psize = sysconf(_SC_PAGE_SIZE);
	t_alloc *alloc = get_alloc(psize * 200);

	return (alloc);
}

t_alloc	*get_small() {
	long int psize = sysconf(_SC_PAGE_SIZE);
	t_alloc *alloc = get_alloc(psize * 4 * 200);

	return (alloc);
}

t_alloc	*get_large(size_t size) {
	long int psize = sysconf(_SC_PAGE_SIZE);
	int pnumber = size / psize;
	pnumber += 1;
	
	t_alloc *alloc = get_alloc(pnumber * psize);

	return (alloc);
}

void	init_malloc() {
	alloc_map.tiny = get_tiny();
	alloc_map.small = get_small();
	alloc_map.large = NULL;
}