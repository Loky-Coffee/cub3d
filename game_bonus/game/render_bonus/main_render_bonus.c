#include "../../include/cub3d.h"

void render_minimap(void) // PUT TO BONUS AFTER FINISHING
{
	t_color clr;
	double start_angle;
	double delta;
	int num_rays = game()->img->width;
	int i = 0;
	
	clr.color = 0x00FF00FF;
	
	ren_draw_table(game()->img, game()->map->map);
	ren_draw_circle(game()->img, 10 + game()->player.pos.x * MAP_SCALE, 10 + game()->player.pos.y * MAP_SCALE, 3, clr.color);
	game()->player.angle = normalize_angle(game()->player.angle);
	start_angle = normalize_angle(game()->player.angle - FOV / 2);
	delta = FOV / num_rays;
	while (i < num_rays)
	{
		cast_ray_n_draw(game()->img, start_angle, clr.color, true);
		start_angle = normalize_angle(start_angle + delta);
		i++;
	}
}

/*
*	HERE WE CAN ADD ALL THE BONUS ELEMENTS WHEN THE TIME HAS COME
*
*/
void render_loop(void *param)
{
	t_game *game;

	game = (t_game *)param;

	wait_for_fps();

	render_movement();
	render_view(game);
	ren_draw_circle(game->img, game->img->width / 2, game->img->height / 2, 2, 0xFFFFFFFF);
	render_minimap();
}

int	main_render(t_map *map)
{
	if (initialise_game(map) != 0)
		return (1);
	main_hooks();
	mlx_loop(game()->mlx);
	return (0);
}
