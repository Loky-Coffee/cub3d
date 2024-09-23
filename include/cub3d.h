// PLEASE KEINE HEADER HIER IST DIE HAUPT HEADER UND KANN SEIN DAS WIR BEIDE HIER WAS SCHREIBEN MUSSEN!!!!

#ifndef CUB3D
# define CUB3D

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
#include "./libft.h"
#include "./MLX42.h"

# ifndef MAX_PATH_LENGTH
#  define MAX_PATH_LENGTH 4096
# endif

// muss am ende sein wegen prototypes die unsere funktionen benutzen

typedef struct s_map
{
	char		map_name[255];
	char		**map;
	char		north_texture[MAX_PATH_LENGTH];
	char		south_texture[MAX_PATH_LENGTH];
	char		west_texture[MAX_PATH_LENGTH];
	char		east_texture[MAX_PATH_LENGTH];
	int			player_pos_x;
	int			player_pos_y;
	u_int32_t	floor;
	u_int32_t	ceiling;
	int			map_width;
	int			map_height;
	//add actual open png in mlx
}t_map;

#include "parsing.h"
#include "render.h"

#endif
