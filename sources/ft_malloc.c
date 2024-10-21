#include "./../header/ft_malloc.h"

t_map alloc_map;

void	*ft_malloc(size_t size) { //change name to malloc (header, file and function)
	static bool init = false;
	if (init == false) {
		init_malloc();
		init = true;
	}
	return(alloc_map.tiny->chunks->address); // to change
}