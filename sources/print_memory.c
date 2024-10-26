#include "./../header/ft_malloc.h"

extern t_map alloc_map;

void	hexa_address(unsigned long int num)
{
	int		modulo;
	char	buff[25];
	int		a;

	a = 0;
	if (!num)
		write(1, "NULL", 4);
	while (num != 0)
	{
		modulo = num % 16;
		num = num / 16;
		buff[a++] = "0123456789abcdef"[modulo];
	}
	while (--a >= 0)
		write (1, &buff[a], 1);
}

void	print_address(void *num)
{
	if (num)
		write(1, "0x", 2);
	hexa_address((unsigned long int) num);
}

void	putnbr_rec(size_t nbpos)
{
	char	p;

	if (nbpos == 0)
		return ;
	putnbr_rec(nbpos / 10);
	p = nbpos % 10 + '0';
	write(1, &p, 1);
}

void	putnbr(size_t nb)
{
	if (nb == 0)
	{
		write(1, "0", 1);
		return ;
	}
	putnbr_rec(nb);
}

void	print_alloc(t_chunk *chunk) {
	if (chunk == NULL)
		return ;
	if (chunk->allocable == true)
		print_alloc(chunk->next);
	else {
		t_chunk *next_chunk = chunk->next;
		print_address((void *)((char *)chunk + sizeof(t_chunk)));
		write(1, " - ", 3);
		print_address((void *)((char *)chunk + sizeof(t_chunk) + chunk->size));
		write(1, " : ", 3);
		putnbr(chunk->size);
		write(1, " bytes\n", 7);
		print_alloc(chunk->next);
	}
}

int	count_bytes(t_chunk *chunk) {
	if (chunk == NULL)
		return (0);
	if (chunk->allocable == true)
		return (count_bytes(chunk->next));
	else
		return (count_bytes(chunk->next) + chunk->size);
}

void	print_total_bytes() {
	size_t size = count_bytes(alloc_map.tiny) + count_bytes(alloc_map.small) + count_bytes(alloc_map.large);
	putnbr(size);
}

void	show_alloc_mem() {
	write(1, "TINY : ", 7);
	print_address(alloc_map.tiny);
	write(1, "\n", 1);
	print_alloc(alloc_map.tiny);

	write(1, "SMALL : ", 8);
	print_address(alloc_map.small);
	write(1, "\n", 1);
	print_alloc(alloc_map.small);

	write(1, "LARGE : ", 8);
	print_address(alloc_map.large);
	write(1, "\n", 1);
	print_alloc(alloc_map.large);

	write(1, "Total : ", 8);
	print_total_bytes();
	write(1, "\n", 1);
}