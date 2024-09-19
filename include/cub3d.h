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

// muss am ende sein wegen prototypes die unsere funktionen benutzen
#include "parsing.h"
#include "render.h"

typedef struct s_map
{
	char	*map_name;
	char	**map;
	char	north_texture[MAX_PATH_LENGTH];
	char	south_texture[MAX_PATH_LENGTH];
	char	west_texture[MAX_PATH_LENGTH];
	char	east_texture[MAX_PATH_LENGTH];
	t_color	floor;
	t_color	ceiling;
}t_map;

#endif