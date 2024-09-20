#include "../../include/cub3d.h"

//					---BLUEPRINT---					//
	// create mlx window instance
	// create plazer vector and pixel and draw it
	// create map array by hand
	// print pixels 64 x 64 onto the window
	// start the raycasting


//					---TODO:---					//
	//TODO: add connection to main struct


void render_game(void)
{
	t_color clr;
	int i = 7;
	
	clr.color = 0x00FF00FF;

	clear_image(game()->img);

	ren_draw_table(game()->img, game()->map->map,  game()->map->map_height, game()->map->map_width); // FILL IN ACTUAL HEIGHT AND WIDTH

	while(i != 0)
		ren_draw_circle(game()->img, game()->player.pos.x, game()->player.pos.y, i--, clr.color);

	cast_ray_n_draw(game()->img, game()->player.angle, clr, true);
}

void render_movement(void)
{
	if (game()->player.move_up)
        game()->player.pos.y -= 1.50;
    if (game()->player.move_down)
        game()->player.pos.y += 1.50;
    if (game()->player.move_left)
        game()->player.pos.x -= 1.50;
    if (game()->player.move_right)
        game()->player.pos.x += 1.50;
	if (game()->player.look_right)
        game()->player.angle += 0.15;
	else if (game()->player.look_left)
        game()->player.angle -= 0.15;
	if (game()->player.angle < 0)
		game()->player.angle += 2 * PI;
	if (game()->player.angle > 2 * PI)
		game()->player.angle -= 2 * PI;
}

// void cast_ray()

void render_loop(void *param)
{
	(void)param;
	render_movement();
	render_game();
}

int	main_render(t_map *map)
{
	t_color clr;
	clr.color = 0x00FF00FF;

	if (initialise_game(map) != 0)
		return (1);
	
	//========--TESTING--========//
	main_hooks();

	//===========================//

	mlx_loop(game()->mlx);

	mlx_terminate(game()->mlx);
	
	// exit funciton
	return (0);
}
