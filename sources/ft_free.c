#include "./../header/ft_malloc.h"

extern t_map alloc_map;

t_chunk	*find_prev(t_chunk *stack, t_chunk *to_find) {
	while (stack != NULL) {
		if (stack == to_find)
			return (to_find);
		if (stack->next == to_find)
			return (stack);
		else
		stack = stack->next;
	}
	return (NULL);
}

void	free_large(t_chunk *chunk, long int psize) {
	chunk->size += sizeof(t_chunk);
	if (chunk->size % psize != 0)
		chunk->size = ((chunk->size / psize) * psize + psize);
	t_chunk *prev = find_prev(alloc_map.large, chunk);
	if (prev == NULL)
		return ;
	else if (prev == chunk)
		alloc_map.large = chunk->next;
	else
		prev->next = chunk->next;
	munmap(chunk, chunk->size);
	return ;
}

void	glue_front(t_chunk *chunk) {
	t_chunk *nxt = chunk->next;
	if (nxt == NULL)
		return ;
	if (nxt->allocable == false)
		return ;
	chunk->next = nxt->next;
	chunk->size = chunk->size + nxt->size + sizeof(t_chunk);
	return ;
}

void	glue_back(t_chunk *chunk, t_chunk *prev) {
	if (prev->allocable == false)
		return ;
	prev->next = chunk->next;
	prev->size = prev->size + chunk->size + sizeof(t_chunk);
	return ;
}

void	free_stack(t_chunk *chunk, long int psize) {
	chunk->allocable = true;
	if (chunk->size % 8 != 0)
		chunk->size = ((chunk->size / 8) * 8 + 8);
	t_chunk *prev;
	if (chunk->size <= (size_t)psize)
		prev = find_prev(alloc_map.tiny, chunk);
	else
		prev = find_prev(alloc_map.small, chunk);
	if (prev == NULL)
		return ;
	else if (prev == chunk)
		glue_front(chunk);
	else {
		glue_front(chunk);
		glue_back(chunk, prev);
	}
	return ;
}

void	ft_free(void *ptr) {
	if (ptr == NULL)
		return ;

	long int psize = sysconf(_SC_PAGE_SIZE);
	t_chunk *chunk = (t_chunk *)((char *)ptr - sizeof(t_chunk));
	
	if (chunk->size <= (size_t)psize * 4) {
		free_stack(chunk, psize);
	}
	else
		free_large(chunk, psize);
}
