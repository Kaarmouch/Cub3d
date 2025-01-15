NAME = CUBE3D
CC = gcc
FLAGS = -Wall -Wextra -Werror
MLX_PATH = ./minilibx/
MLX_LIB = $(MLX_PATH)libmlx.a
MLX_FLAGS = -lX11 -lXext -lm
C_FILE = main.c out.c utils.c load.c gnl.c build_cube.c \
         b_utils.c draw.c d_utils.c build_color.c clean_init.c input.c
SRC_DIR = ./src/
SRC = $(addprefix $(SRC_DIR), $(C_FILE))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB)
	@echo "Linking executable $(NAME)..."
	$(CC) $(FLAGS) $(OBJ) $(MLX_LIB) $(MLX_FLAGS) -o $@
	@echo "$(NAME) built successfully."

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	@echo "Compiling $<..."
	$(CC) $(FLAGS) -c $< -o $@

$(MLX_LIB):
	@echo "Building MinilibX in $(MLX_PATH)..."
	$(MAKE) -C $(MLX_PATH)

clean:
	@echo "Cleaning object files..."
	$(MAKE) -C $(MLX_PATH) clean
	rm -f $(OBJ)
	@echo "Object files removed."

fclean: clean
	@echo "Cleaning executable $(NAME)..."
	rm -f $(NAME)
	@echo "$(NAME) removed."

re: fclean all

.PHONY: all clean fclean re

