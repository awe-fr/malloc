#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/resource.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_chunk {
	bool	allocable;
	size_t	size;
	void	*address;
    struct s_chunk *next;
}	t_chunk;

typedef struct s_alloc {
	size_t	count;
	t_chunk *chunks;
    struct s_alloc *next;
}	t_alloc;

typedef struct s_map {
	t_alloc	*tiny;
	t_alloc *small;
	t_alloc *large;
}	t_map;


////////////////Init////////////////

t_alloc	*get_alloc(long int psize);
t_alloc	*get_tiny();
t_alloc	*get_small();
t_alloc	*get_large(size_t size);
void	init_malloc();



// void	free(void *ptr);
void	*ft_malloc(size_t size);
// void	*realloc(void *ptr, size_t size);

#endif