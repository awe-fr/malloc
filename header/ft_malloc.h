#ifndef FT_MALLOC_H
# define FT_MALLOC_H

///////////////Include///////////////

# include <sys/resource.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <unistd.h>
#include <stdio.h> //to remove

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
int	init_malloc();

////////////////Print////////////////

void	hexa_address(unsigned long int num);
void	print_address(void *num);
void	putnbr_rec(size_t nbpos);
void	putnbr(size_t nb);
void	print_alloc(t_chunk *chunk);
int	count_bytes(t_chunk *chunk);
void	print_total_bytes();
void	show_alloc_mem();



// void	free(void *ptr);
void	*ft_malloc(size_t size);
// void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();

#endif