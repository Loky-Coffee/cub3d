CC = cc # Compiler
CFLAGS = -Wall -Wextra -Werror -Iinclude -g -Ofast -fsanitize=address

# LIBS
LIB_MLX = ./include/libmlx42.a 
LIBFT = ./include/libft.a
MLX = ./include/libmlx42.a -lglfw

# OBJECT
OBJ_DIR = obj/
OBJ_DIR_BONUS = obj_bonus/

# SOURCE
SRC_DIR = game
SRC_DIR_BONUS = game_bonus

# MANDATORY
SRC_PARSING = $(wildcard $(SRC_DIR)/parsing/*.c)
SRC_RENDER = $(wildcard $(SRC_DIR)/render/*.c)
SRC_MAIN = $(SRC_DIR)/main.c

SRC = $(SRC_PARSING) $(SRC_RENDER) $(SRC_MAIN)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)%.o, $(SRC))
NAME = cub3D

# BONUS
SRC_PARSING_BONUS = $(wildcard $(SRC_DIR_BONUS)/parsing_bonus/*_bonus.c)
SRC_RENDER_BONUS = $(wildcard $(SRC_DIR_BONUS)/render_bonus/*_bonus.c)
SRC_MAIN_BONUS = $(SRC_DIR_BONUS)/main_bonus.c

SRC_BONUS = $(SRC_PARSING_BONUS) $(SRC_RENDER_BONUS) $(SRC_MAIN_BONUS)
OBJ_BONUS = $(patsubst $(SRC_DIR_BONUS)/%.c, $(OBJ_DIR_BONUS)%.o, $(SRC_BONUS))
NAME_BONUS = cub3D_bonus

# RULES - MANDATORY
all: $(LIB_MLX) $(NAME)

$(NAME): libft $(OBJ) $(LIB_MLX) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX)
	@echo "Build abgeschlossen: $(NAME)"

$(OBJ_DIR)%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# RULES - BONUS
bonus: $(LIB_MLX) $(NAME_BONUS)

$(NAME_BONUS): libft $(OBJ_BONUS) $(LIB_MLX) $(OBJ_DIR_BONUS)
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFT) $(MLX)
	@echo "Bonus-Build abgeschlossen: $(NAME_BONUS)"

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS):
	@mkdir -p $(OBJ_DIR_BONUS)

################################ CLEANING RULES ################################

clean:
	@rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@rm -f /include/libft.*
	@echo "Objektdateien gelöscht"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "Programmdateien gelöscht"

re: fclean all

############################## MLX42_BUILD_RULES ###############################

$(LIB_MLX):
	@git clone https://github.com/codam-coding-college/MLX42.git
	@cd MLX42; cmake -B build; cmake --build build -j4
	@cp MLX42/build/libmlx42.a ./include
	@cp MLX42/include/MLX42/MLX42.h ./include
	@rm -rf MLX42

clean_mlx:
	@rm -rf MLX42
	@rm -f ./include/MLX42.h
	@rm -f ./include/libmlx42.a
	@rm -f ./include_bonus/MLX42.h
	@rm -f ./include_bonus/libmlx42.a
	@echo "MLX42-Dateien gelöscht"

############################### LIBFT_BUILD_RULES ##############################

LIBFT_OBJ_DIR = libft/obj/
LIBFT_SRC_DIR = libft/src/

$(LIBFT_OBJ_DIR)%.o: $(LIBFT_SRC_DIR)%.c
	@mkdir -p $(LIBFT_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	@cd include/libft && make
	@cp include/libft/libft.h ./include
	@cp include/libft/libft.a ./include

re_libft:
	@cd include/libft && make re

clean_libft:
	@cd include/libft && make clean

fclean_libft: clean_libft
	@cd include/libft && make fclean
	@rm ./include/libft.*
	@rm ./include_bonus/libft.*

################################# EXTRA_RULES ##################################

.PHONY: all clean fclean re libft re_libft clean_libft fclean_libft mlx clean_mlx bonus

fcleanall: fclean fclean_libft clean_mlx
	@echo "Alle Dateien komplett gelöscht"
