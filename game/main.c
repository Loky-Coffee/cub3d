// PLEASE KEINE HEADER HIER IST DIE HAUPT MAIN UND KANN SEIN DAS WIR BEIDE HIER WAS SCHREIBEN MUSSEN!!!!

#include "../include/cub3d.h"

void init_cub3d_h(t_map *map)
{
	ft_memset(map->map_name, '\0', sizeof(map->map_name));
	ft_memset(map->north_texture, '\0', sizeof(map->north_texture));
	ft_memset(map->south_texture, '\0', sizeof(map->south_texture));
	ft_memset(map->west_texture, '\0', sizeof(map->west_texture));
	ft_memset(map->east_texture, '\0', sizeof(map->east_texture));
	map->map = NULL;
	map->player_pos_x = 0;
	map->player_pos_y = 0;
	map->floor = 0;
	map->ceiling = 0;
}

int main(int argc, char **argv)
{
	t_p parsing;
	t_map main_struct;

	init_cub3d_h(&main_struct);
	(void)argc; // for testing purposes only
	(void)argv;
	if (main_parsing(argc, argv, &main_struct, &parsing) != 0)
		return (EXIT_FAILURE);
	// if (main_render() != 0)
	//     return (EXIT_FAILURE);

	int i = 0;
	printf("-----------------------------------------------------------\n");
	while (main_struct.map[i])
		printf("map->map: %s\n", main_struct.map[i++]);
	printf("-----------------------------------------------------------\n");
	printf("map->map_name: %s\n", main_struct.map_name);
	printf("-----------------------------------------------------------\n");
	printf("map->north_texture: %s\n", main_struct.north_texture);
	printf("-----------------------------------------------------------\n");
	printf("map->south_texture: %s\n", main_struct.south_texture);
	printf("-----------------------------------------------------------\n");
	printf("map->west_texture: %s\n", main_struct.west_texture);
	printf("-----------------------------------------------------------\n");
	printf("map->east_texture: %s\n", main_struct.east_texture);
	printf("-----------------------------------------------------------\n");
	printf("map->player_pos_x: %d\n", main_struct.player_pos_x);
	printf("-----------------------------------------------------------\n");
	printf("map->player_pos_y: %d\n", main_struct.player_pos_y);
	printf("-----------------------------------------------------------\n");
	printf("map->floor: %d\n", main_struct.floor);
	printf("-----------------------------------------------------------\n");
	printf("map->ceiling: %d\n", main_struct.ceiling);
	printf("-----------------------------------------------------------\n");
	return (EXIT_SUCCESS);
}
