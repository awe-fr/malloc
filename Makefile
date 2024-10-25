NAME = malloc

SRCS = ./main.c\
		./sources/ft_malloc.c\
		./sources/init.c\
		./sources/print_memory.c\

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -g

RM = rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(OBJS) -o $(NAME)

%.o: 			%.c
				$(CC) $(CFLAGS) -c $< -o $@
				
clean:
			$(RM) $(OBJS)
			
fclean:		clean
			$(RM) $(NAME)
			
re:			fclean all

.PHONY:		all clean fclean re