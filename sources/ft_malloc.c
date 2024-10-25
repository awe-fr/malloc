#include "./../header/ft_malloc.h"

t_map alloc_map;

void	*manage_chunk(size_t size, t_chunk *chunk) {
	t_chunk *new_chunk;

	size_t total_len = chunk->size;
	size_t new_size = total_len - (size + sizeof(t_chunk));

	new_chunk = (t_chunk *)((char *)chunk + sizeof(t_chunk) + new_size);
	new_chunk->allocable = false;
	new_chunk->size = size;
	new_chunk->next = chunk->next;
	
	chunk->size = new_size;
	chunk->next = new_chunk;

	return ((t_chunk *)((char *)new_chunk + sizeof(t_chunk)));
}

void	*find_space(size_t size, t_chunk *inspect) {
	if (inspect->size > size + sizeof(t_chunk)) {
		return (manage_chunk(size, inspect));
	}
	else if (inspect->size >= size) {
		inspect->allocable = false;
		return (inspect + sizeof(t_chunk));
	}
	else
		return (NULL);
}

void	*alloc_tiny(size_t size) {
	if (size % 8 != 0) {
		size = ((size / 8) * 8 + 8);
	}
	return(find_space(size, alloc_map.tiny));
}

void	*alloc_small(size_t size) {
	if (size % 8 != 0) {
		size = ((size / 8) * 8 + 8);
	}
	return(find_space(size, alloc_map.small));
}

void	*alloc_large(size_t size) {
	long int psize = sysconf(_SC_PAGE_SIZE);
	if ((size + sizeof(t_chunk)) % psize != 0) {
		size = ((size / psize) * psize + psize);
	}
	void *allocation = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (allocation == MAP_FAILED)
		return (NULL);
	t_chunk *chunk = allocation;
	
	chunk->allocable = false;
	chunk->size = size - sizeof(t_chunk);
	if (alloc_map.large == NULL)
		chunk->next = NULL;
	else
		chunk->next = alloc_map.large;
	alloc_map.large = chunk;
	
	return((void *)((char *)chunk + sizeof(t_chunk)));
}

void	*ft_malloc(size_t size) { //change name to malloc (header, file and function)
	static bool init = false;
	if (init == false) {
		if (init_malloc() == -1)
			return (NULL);
		init = true;
	}
	long int psize = sysconf(_SC_PAGE_SIZE);

	if (size <= psize) {
		return (alloc_tiny(size));
	} 
	else if (size <= (psize * 4)) {
		return(alloc_small(size));
	}
	else
		return(alloc_large(size));
}