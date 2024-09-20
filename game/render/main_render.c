#include "../../include/cub3d.h"

//					---BLUEPRINT---					//
	// create mlx window instance
	// create plazer vector and pixel and draw it
	// create map array by hand
	// print pixels 64 x 64 onto the window
	// start the raycasting


//					---TODO:---					//
	//TODO: CHANGE ALL DOBLES TO FLOATS


double normalize_angle(double angle)
{
	if (angle <= 0)
		angle += RA;
	if (angle > RA)
		angle -= RA;
	return (angle);
}

void render_view(t_color clr)
{
	double start_angle;
	double endin_angle;
	double delta;

	game()->player.angle = normalize_angle(game()->player.angle);

	start_angle = normalize_angle(game()->player.angle - (double)(FOV / 2));
	endin_angle = normalize_angle(game()->player.angle + (double)(FOV / 2));
	
	delta = (double)FOV / STD_WIDTH; //TODO: change to actual SIZE of window

	while(start_angle < endin_angle || (endin_angle < start_angle && start_angle < RA))
	{
		cast_ray_n_draw(game()->img, start_angle, clr, true);
		start_angle = normalize_angle(start_angle + delta);
	}
}


void render_game(void)
{
	int i;
	t_color clr;

	i = 4;
	clr.color = 0x00FF00FF;
	clear_image(game()->img);
	ren_draw_table(game()->img, game()->map->map,  game()->map->map_height, game()->map->map_width); // FILL IN ACTUAL HEIGHT AND WIDTH

	while(i != 0)
		ren_draw_circle(game()->img, game()->player.pos.x, game()->player.pos.y, i--, clr.color);
	render_view(clr);
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
