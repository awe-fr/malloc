ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LINK = libft_malloc.so

SRCS =	./sources/print_memory.c\
		./sources/ft_realloc.c\
		./sources/ft_malloc.c\
		./sources/ft_free.c\
		./sources/init.c\

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -fPIC

RM = rm -f

all:			$(NAME) $(LINK)

$(NAME):		$(OBJS)
				$(CC) $(OBJS) -shared -o $(NAME) $(CFLAGS)

$(LINK):		$(NAME)
				ln -sf $(NAME) $(LINK)

%.o: 			%.c
				$(CC) $(CFLAGS) -c $< -o $@
				
clean:
			$(RM) $(OBJS)
			
fclean:		clean
			$(RM) $(NAME) $(LINK)
			
re:			fclean all

.PHONY:		all clean fclean re