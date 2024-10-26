#include "./../header/ft_malloc.h"

extern t_map alloc_map;

t_chunk *find_prev(t_chunk *stack, t_chunk *to_find) {
    if (stack == NULL)
        return (NULL);
    if (stack == to_find)
        return (to_find);
    if (stack->next == to_find)
        return (stack);
    else
        return (find_prev(stack->next, to_find));
}

void    free_large(t_chunk *chunk, long int psize) {
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

void	ft_free(void *ptr) { //change name to free (header, file and function)
    if (ptr == NULL)
        return ;

    long int psize = sysconf(_SC_PAGE_SIZE);
    t_chunk *chunk = (t_chunk *)((char *)ptr - sizeof(t_chunk));
    
    if (chunk->size <= psize * 4) {
        chunk->allocable = true;
        if (chunk->size % 8 != 0)
            chunk->size = ((chunk->size / 8) * 8 + 8);
        // defragmentation of memory
    }
    else
        free_large(chunk, psize);
}
