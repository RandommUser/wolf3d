NAME=wolf3d
SRCS=editor.c\
	editor_actions.c\
	editor_coloring.c\
	editor_textures.c\
	editor_loops.c\
	exit.c\
	helpers.c\
	image.c\
	map_writer.c\
	struct.c\
	key_active.c\
	main.c
BIGO=$(SRCS:.c=.o)
INC=-I ./minilibx -I libft 
LIB=-L ./minilibx -lmlx -L ./libft -lft 
FLAGS=-Wall -Wextra -Werror
FRAMEWORK=-framework OpenGL -framework AppKit 
PREFRAMEWORK=-lpthread -pthread 


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
