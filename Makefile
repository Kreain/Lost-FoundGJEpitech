NAME	=	lostandfound

SRC	=	main.c	\
		map.c	\
		jeu.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall

LDFLAGS	=	-lcsfml-graphics -lcsfml-window -lcsfml-audio -lcsfml-system

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re test