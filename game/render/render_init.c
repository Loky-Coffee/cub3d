#include "../../include/cub3d.h"

int initialise_game(void)
{
	// mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game()->mlx = mlx_init(STD_WIDTH, STD_HEIGHT, "CUB-3D", true);
	if (!game()->mlx)
		return (1);
	game()->img = mlx_new_image(game()->mlx, STD_WIDTH, STD_HEIGHT);
	if (!game()->img)
		return (1);
	mlx_image_to_window(game()->mlx, game()->img, 0, 0);

	game()->player.pos.x = 96;
	game()->player.pos.y = 96;

	return (0);
}