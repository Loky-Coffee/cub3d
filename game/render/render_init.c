#include "../../include/cub3d.h"

int initialise_mlx(void)
{
	// mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game()->mlx = mlx_init(STD_WIDTH, STD_HEIGHT, "CUB-3D", true);
	if (game()->mlx == NULL)
		return (1);
	game()->img = mlx_new_image(game()->mlx, STD_WIDTH, STD_HEIGHT);
	if (game()->img == NULL)
		return (1);
	mlx_image_to_window(game()->mlx, game()->img, 0, 0);
	return (0);
}

void	initialise_map_size(void)
{
	int x;
	int	y;

	y = 0;
	while(game()->map->map[y] != NULL)
	{
		x = 0;
		while(game()->map->map[y][x] != '\0')
			x++;
		if (x > game()->map->map_width)
			game()->map->map_width = x;
		y++;
	}
	game()->map->map_height = y;
}

int initialise_game(t_map *map)
{
	game()->mlx = NULL;
	game()->img = NULL;
	game()->map = map;
	game()->player.pos.x = (double)game()->map->player_pos_x * TILE + (TILE / 2);
	game()->player.pos.y = (double)game()->map->player_pos_y * TILE + (TILE / 2);
	game()->player.angle = 0;
	game()->player.move_up = false;
	game()->player.move_down = false;
	game()->player.move_left = false;
	game()->player.move_right = false;
	game()->player.look_right = false;
	game()->player.look_left = false;

	initialise_map_size();
	if (initialise_mlx() != 0)
		return (1);
	return (0);
}
