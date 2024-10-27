#include "./../header/ft_malloc.h"

extern t_map alloc_map;

void	*my_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*destpasta;
	const char	*srcpasta;

	if (dest == NULL || src == NULL)
		return (NULL);
	i = 0;
	destpasta = dest;
	srcpasta = src;
	while (i < n)
	{
		destpasta[i] = srcpasta[i];
		i++;
	}
	dest = destpasta;
	return ((void *) dest);
}

void	*realloc_large(t_chunk *chunk, void *ptr, size_t size) {
	void *new_alloc = ft_malloc(size);
	if (new_alloc == NULL)
		return (NULL);
	new_alloc = my_memcpy(new_alloc, ptr, size);
	if (size < chunk->size)
		new_alloc = my_memcpy(new_alloc, ptr, size);
	else
		new_alloc = my_memcpy(new_alloc, ptr, chunk->size);
	ft_free(ptr);
	return (new_alloc);
}

void	*realloc_smaller(t_chunk *chunk, void *ptr, size_t size) {
	size_t full_size = chunk->size;
	if (full_size % 8 != 0)
		full_size = ((full_size / 8) * 8 + 8);
	if (size <= full_size && size > full_size - 8) {
		chunk->size = size;
		return (ptr);
	}
	void *new_alloc = ft_malloc(size);
	if (new_alloc == NULL)
		return (NULL);
	new_alloc = my_memcpy(new_alloc, ptr, size);
	if (size < chunk->size)
		new_alloc = my_memcpy(new_alloc, ptr, size);
	else
		new_alloc = my_memcpy(new_alloc, ptr, chunk->size);
	ft_free(ptr);
	return (new_alloc);
}

void	*realloc_sort(t_chunk *chunk, void *ptr, size_t size) {
	long int psize = sysconf(_SC_PAGE_SIZE);
	if (chunk->size == size)
		return (ptr);
	if (chunk->size <= psize * 4) {
		return (realloc_smaller(chunk, ptr, size));
	}
	else
		return (realloc_large(chunk, ptr, size));
}

void	*ft_realloc(void *ptr, size_t size) {
	if (ptr == NULL)
		return(ft_malloc(size));
	if (size == 0){
		ft_free(ptr);
		return (NULL);
	}
	t_chunk	*chunk = (t_chunk *)((char *)ptr - sizeof(t_chunk));
	return (realloc_sort(chunk, ptr, size));
}

