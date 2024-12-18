#include "./../header/ft_malloc.h"

t_map alloc_map;

void	*manage_chunk(size_t real_size, size_t size, t_chunk *chunk) {
	t_chunk *new_chunk;

	size_t total_len = chunk->size;
	size_t new_size = total_len - (size + sizeof(t_chunk));

	new_chunk = (t_chunk *)((char *)chunk + sizeof(t_chunk) + new_size);
	new_chunk->allocable = false;
	new_chunk->size = real_size;
	new_chunk->next = chunk->next;
	
	chunk->size = new_size;
	chunk->next = new_chunk;

	return ((void *)((char *)new_chunk + sizeof(t_chunk)));
}

void	*cut_free_chunk(size_t real_size, size_t size, t_chunk *inspect) {
	t_chunk	*new_chunk = (t_chunk *)((char *)inspect + size + sizeof(t_chunk));

	new_chunk->allocable = true;
	new_chunk->size = (inspect->size - sizeof(t_chunk)) - size;
	new_chunk->next = inspect->next;

	inspect->allocable = false;
	inspect->next = new_chunk;
	inspect->size = real_size;

	return ((void *)((char *)inspect + sizeof(t_chunk)));
}

void	*find_free(size_t real_size, size_t size, t_chunk *inspect) {
	while (inspect != NULL) {
		if (inspect->allocable == false)
			inspect = inspect->next;
		else if (inspect->size > size + sizeof(t_chunk))
			return (cut_free_chunk(real_size, size, inspect));
		else if (inspect->size == size) {
			inspect->allocable = false;
			inspect->size = real_size;
			return ((void *)((char *)inspect + sizeof(t_chunk)));
		}
		else
			inspect = inspect->next;
	}
	return (NULL);
}

void	*find_space(size_t real_size, size_t size, t_chunk *inspect) {
	if (inspect->size > size + sizeof(t_chunk))
		return (manage_chunk(real_size, size, inspect));
	else if (inspect->size == size) {
		inspect->allocable = false;
		inspect->size = real_size;
		return ((void *)((char *)inspect + sizeof(t_chunk)));
	}
	else
		return (find_free(real_size, size, inspect));
}

void	*alloc_tiny(size_t size) {
	size_t	real_size = size;
	if (size % 8 != 0)
		size = ((size / 8) * 8 + 8);
	return(find_space(real_size, size, alloc_map.tiny));
}

void	*alloc_small(size_t size) {
	size_t	real_size = size;
	if (size % 8 != 0)
		size = ((size / 8) * 8 + 8);
	return(find_space(real_size, size, alloc_map.small));
}

void	*alloc_large(size_t size) {
	size_t	real_size = size;
	size += sizeof(t_chunk);
	long int psize = sysconf(_SC_PAGE_SIZE);
	if (size % psize != 0)
		size = ((size / psize) * psize + psize);
	void *allocation = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (allocation == MAP_FAILED)
		return (NULL);
	t_chunk *chunk = allocation;
	
	chunk->allocable = false;
	chunk->size = real_size;
	if (alloc_map.large == NULL)
		chunk->next = NULL;
	else
		chunk->next = alloc_map.large;
	alloc_map.large = chunk;
	
	return((void *)((char *)chunk + sizeof(t_chunk)));
}

void	*ft_malloc(size_t size) {
	static bool init = false;
	if (init == false) {
		if (init_malloc() == -1)
			return (NULL);
		init = true;
	}
	long int psize = sysconf(_SC_PAGE_SIZE);
	if (size == 0)
		return (NULL);
	if (size <= (size_t)psize)
		return (alloc_tiny(size));
	else if (size <= ((size_t)psize * 4))
		return(alloc_small(size));
	else
		return(alloc_large(size));
}