#ifndef MALLOC_H
# define MALLOC_H

# include <sys/resource.h>
# include <sys/mman.h>
# include <unistd.h>

// void	free(void *ptr);
void	*malloc(size_t size);
// void	*realloc(void *ptr, size_t size);

#endif