# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 20:13:53 by aalatzas          #+#    #+#              #
#    Updated: 2024/09/17 20:13:59 by aalatzas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIB_MLX = ./include/libmlx42.a
LIBFT = ./include/libft.a
MLX = ./include/libmlx42.a -Iinclude -lglfw

# Verzeichnisse
OBJ_DIR = obj/object_mandatory/
SRC_DIR = game

# Quellcodedateien
SRC_PARSING = $(wildcard $(SRC_DIR)/parsing/*.c)
SRC_RENDER = $(wildcard $(SRC_DIR)/render/*.c)
SRC_MAIN = $(SRC_DIR)/main.c

SRC = $(SRC_PARSING) $(SRC_RENDER) $(SRC_MAIN)

# Objektdateien
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)%.o, $(SRC))

# Name des Programms
NAME = cub3D

# Regeln
all: $(NAME)

$(NAME): $(OBJ) libft $(LIB_MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX)
	@echo "Build abgeschlossen: $(NAME)"

$(OBJ_DIR)%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
clean:
	@rm -f $(OBJ)
	@rm -f /include/libft.*
	@echo "Objektdateien gelöscht"

fclean: clean
	@rm -f $(NAME)
	@echo "Programmdateien gelöscht"

re: fclean all

############################ CUB3D BONUS_PART_RULES ############################
# Hier kannst du den Bonus-Part hinzufügen, falls benötigt.

############################## MLX42_BUILD_RULES ###############################
$(LIB_MLX):
	@git clone https://github.com/codam-coding-college/MLX42.git
	@cd MLX42; cmake -B build; cmake --build build -j4
	@mv MLX42/build/libmlx42.a ./include
	@mv MLX42/include/MLX42/MLX42.h ./include
	@rm -rf MLX42

clean_mlx:
	@rm -rf MLX42
	@rm -f ./include/MLX42.h
	@rm -f ./include/libmlx42.a
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

################################# EXTRA_RULES ##################################
.PHONY: all clean fclean re libft re_libft clean_libft fclean_libft mlx clean_mlx
fcleanall: fclean fclean_libft clean_mlx
	@echo "Alle Dateien komplett gelöscht"