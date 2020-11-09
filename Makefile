NAME=wolf3d
SRCS=main.c
BIGO=$(SRCS:.c=.o)
INC=-I libft 
LIB=-L ./libft -lft 
FLAGS=-Wall -Wextra -Werror
FRAMEWORK=
PREFRAMEWORK=


all : $(NAME)

$(NAME) :
	make -C ./libft
	gcc -c $(FLAGS) $(SRCS) $(INC)
	gcc $(FLAGS) $(PREFRAMEWORK) -o $(NAME) $(BIGO) $(LIB) $(FRAMEWORK)

clean :
	make -C ./libft clean
	rm -f $(BIGO)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all
