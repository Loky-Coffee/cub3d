#include "../../include/cub3d.h"

void hook_keys(mlx_key_data_t keydata, void *param)
{
	(void)param;

	if (keydata.action == MLX_PRESS || keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W)
			game()->player.move_up = (keydata.action == MLX_PRESS);
		else if (keydata.key == MLX_KEY_A)
			game()->player.move_left = (keydata.action == MLX_PRESS);
		else if (keydata.key == MLX_KEY_S)
			game()->player.move_down = (keydata.action == MLX_PRESS);
		else if (keydata.key == MLX_KEY_D)
			game()->player.move_right = (keydata.action == MLX_PRESS);
		else if (keydata.key == MLX_KEY_RIGHT)
			game()->player.look_right = (keydata.action == MLX_PRESS);
		else if (keydata.key == MLX_KEY_LEFT)
			game()->player.look_left = (keydata.action == MLX_PRESS);
		else if (keydata.key == MLX_KEY_ESCAPE)
			if (game() && game()->mlx)
			{
				mlx_terminate(game()->mlx);
				exit(EXIT_SUCCESS);
				//TODO: add ft_exit function here
			}
	}
}

void hook_resize(int32_t width, int32_t height, void* param)
{
	(void)param;
	mlx_resize_image(game()->img, width, height);
	mlx_image_to_window(game()->mlx, game()->img, 0, 0);
}

// void hook_mouse_cursor(float xpos, float ypos, void * param)
// {
// 	(void)param;
// 	(void)ypos;
// 	static xdelta;

// 	mlx_mouse_get_delta(game()->mlx, xpos, ypos);

// 	game()->player.angle = normalize_angle(game()->player.angle + (xpos / 100));
// }

void main_hooks()
{
	// mlx_cursor_hook(game()->mlx, hook_mouse_cursor, NULL); //TODO: IMPLEMENT AFTER BONUS
	mlx_resize_hook(game()->mlx, hook_resize, NULL);
	mlx_key_hook(game()->mlx,hook_keys, NULL);
	mlx_loop_hook(game()->mlx, render_loop, game());
}
