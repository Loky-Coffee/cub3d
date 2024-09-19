#include "../../include/cub3d.h"

void hook_move(mlx_key_data_t keydata, void *param)
{
	(void)param;

	if (keydata.action == MLX_PRESS || keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_W)
			game()->player.move_up = (keydata.action == MLX_PRESS);
		else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_A)
			game()->player.move_left = (keydata.action == MLX_PRESS);
		else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_S)
			game()->player.move_down = (keydata.action == MLX_PRESS);
		else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_D)
			game()->player.move_right = (keydata.action == MLX_PRESS);
	}
}


void main_hooks()
{
	mlx_key_hook(game()->mlx, hook_move, NULL);
	mlx_loop_hook(game()->mlx, render_loop, NULL);

	// initalise mouse
	//initialise exit keys
	// initiales maybe some extra stuff :)
}