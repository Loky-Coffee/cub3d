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
				ft_exit(EXIT_SUCCESS);
	}
}

void hook_resize(int32_t width, int32_t height, void* param)
{
	(void)param;
	mlx_resize_image(game()->img, width, height);
	mlx_image_to_window(game()->mlx, game()->img, 0, 0);
}

void hook_mouse_cursor(double xpos, double ypos, void * param)
{
	t_game *g = (t_game *)param;
	(void)ypos;
	float xdelta;

	xdelta = g->mouse_delta.x - (float)xpos;
	mlx_set_mouse_pos(g->mlx, g->img->width / 2, g->img->height / 2);
	g->mouse_delta.x = (float)g->img->width / 2;
	g->player.angle = (g->player.angle - (xdelta * SENSITIVITY));
}

void main_hooks()
{
	int32_t mouse_xpos;
	int32_t mouse_ypos;

	//bonus
	mlx_set_cursor_mode(game()->mlx, MLX_MOUSE_HIDDEN);
	mlx_get_mouse_pos(game()->mlx, &mouse_xpos, &mouse_ypos);
	game()->mouse_delta.x = (float)mouse_xpos;
	mlx_cursor_hook(game()->mlx, hook_mouse_cursor, game());
	//mandatory
	mlx_resize_hook(game()->mlx, hook_resize, NULL);
	mlx_key_hook(game()->mlx,hook_keys, NULL);
	mlx_loop_hook(game()->mlx, render_loop, game());
}
