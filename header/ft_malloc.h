#ifndef FT_MALLOC_H
# define FT_MALLOC_H

///////////////Include///////////////

# include <sys/resource.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <unistd.h>

///////////////Struct///////////////

typedef struct s_chunk {
	bool	allocable;
	size_t	size;
    struct s_chunk *next;
}	t_chunk;

typedef struct s_map {
	t_chunk	*tiny;
	t_chunk *small;
	t_chunk *large;
}	t_map;

////////////////Init////////////////

t_chunk	*get_alloc(long int psize);
t_chunk	*get_tiny();
t_chunk	*get_small();
int		init_malloc();

////////////////Print////////////////

size_t	count_bytes(t_chunk *chunk);
void	hexa_address(unsigned long int num);
void	print_alloc(t_chunk *chunk);
void	print_address(void *num);
void	putnbr_rec(size_t nbpos);
void	print_total_bytes();
void	putnbr(size_t nb);
void	show_alloc_mem();

////////////////Free////////////////

t_chunk	*find_prev(t_chunk *stack, t_chunk *to_find);
void	free_large(t_chunk *chunk, long int psize);
void	free_stack(t_chunk *chunk, long int psize);
void	glue_back(t_chunk *chunk, t_chunk *prev);
void	glue_front(t_chunk *chunk);

///////////////Realloc///////////////

void	*realloc_smaller(t_chunk *chunk, void *ptr, size_t size);
void	*realloc_large(t_chunk *chunk, void *ptr, size_t size);
void	*realloc_sort(t_chunk *chunk, void *ptr, size_t size);
void	*my_memcpy(void *dest, const void *src, size_t n);

///////////////Malloc///////////////

void	*cut_free_chunk(size_t real_size, size_t size, t_chunk *inspect);
void	*manage_chunk(size_t real_size, size_t size, t_chunk *chunk);
void	*find_space(size_t real_size, size_t size, t_chunk *inspect);
void	*find_free(size_t real_size, size_t size, t_chunk *inspect);
void	*alloc_small(size_t size);
void	*alloc_large(size_t size);
void	*alloc_tiny(size_t size);

//////////////Funtions//////////////

void	*ft_realloc(void *ptr, size_t size);
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	show_alloc_mem();

#endif