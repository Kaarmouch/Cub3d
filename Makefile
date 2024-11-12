NAME = CUBE3D


FLAGS = -Wall -Wextra -Werror

MLX_FILE	=	libmlx.a

MLX_FLAG	=	-lX11 -lXext -lm

MLX_PATH	=	./minilibx/

MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))

MLX_EX		=	$(MLX_LIB) $(MLX_FLAG)

C_FILE		= main.c  out.c  utils.c load.c gnl.c  build_cube.c\
		b_utils.c draw.c d_utils.c build_color.c  clean_init.c

SRC_DIR		=	./src/

SRC			=	$(addprefix $(SRC_DIR),$(C_FILE))

OBJ			=	$(SRC:.c=.o)

.c.o:
	@$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

gdb: CFLAGS += -o -g 

gdb: all
	gdb ./$(NAME)

valgrind: mlx $(OBJ)
	@echo "\033[0;33m\nCOMPIL-OL..."
	@cc -g3 $(OBJ) $(MLX_EX) -o $(NAME)
	@echo "\033[1;32m$(NAME) executable created"

mlx:
	@echo "\033[0;33m\nCOMPILING $(MLX_PATH)..."
	@make -sC $(MLX_PATH)
	@echo "\033[1;32m$(MLX_FILE) created"

$(NAME): mlx $(OBJ)
	@echo "\033[0;33m\nCOMPILING 7O_OL..."
	@cc $(OBJ) $(MLX_EX) -o $(NAME)
	@echo "\033[1;32m$(NAME) executable created"

clean:
	@echo "\033[0;31mDeleting Obj file in $(MLX_PATH)..."
	@make clean -sC $(MLX_PATH)
	@echo "\033[1;32mDone"
	@echo "\033[0;31mDeleting Obj file in ./src/..."
	@rm -f $(OBJ)
	@echo "\033[1;32mDone"

fclean: clean
	@echo "\033[0;31mDeleting so_many executable..."
	@rm -f $(NAME)
	@echo "\033[1;32mDone"

re: fclean all

.PHONY: all clean fclean re
