#include "../../include/cub3d.h"

//					---BLUEPRINT---					//
	// create mlx window instance
	// create plazer vector and pixel and draw it
	// create map array by hand
	// print pixels 64 x 64 onto the window
	// start the raycasting
	// get the wall height
	// render tha y wall pixels
	// improve the movement
	// get wall colission
	// start printing the textures

//					---TODO:---					//
	//TODO: CHANGE ALL DOBLES TO FLOATS

void render_minimap(void)
{
	t_color clr;
	double start_angle;
	double delta;
	int x;
	int num_rays = STD_WIDTH;
	int i = 0;

	x = 4;
	clr.color = 0x00FF00FF;

	clear_image(game()->img);

	ren_draw_table(game()->img, game()->map->map,  game()->map->map_height / 30, game()->map->map_width / 30); // FILL IN ACTUAL HEIGHT AND WIDTH
	
	while(x != 0)
		ren_draw_circle(game()->img, game()->player.pos.x, game()->player.pos.y, x--, clr.color);
	
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
*	> cosinus is for calculating how much movement is on the X
*	> sinus is for how much on the y
*	> then just multiply it with the speed and the you got your new position
*
*
*/
void render_movement(void)
{
	if (game()->player.move_up)
    {
		game()->player.pos.x += cos(game()->player.angle) * SPEED;
		game()->player.pos.y += sin(game()->player.angle) * SPEED;
	}
    if (game()->player.move_down)
    {
		game()->player.pos.x -= cos(game()->player.angle) * SPEED;
		game()->player.pos.y -= sin(game()->player.angle) * SPEED;
	}
    if (game()->player.move_left)
    {
		game()->player.pos.x -= cos(game()->player.angle + PI / 2) * SPEED;
		game()->player.pos.y -= sin(game()->player.angle + PI / 2) * SPEED;
	}
    if (game()->player.move_right)
    {
		game()->player.pos.x += cos(game()->player.angle + PI / 2) * SPEED;
		game()->player.pos.y += sin(game()->player.angle + PI / 2) * SPEED;
	}
	if (game()->player.look_right)
        game()->player.angle += 0.10;
	else if (game()->player.look_left)
        game()->player.angle -= 0.10;
	game()->player.angle = normalize_angle(game()->player.angle);
}

void render_wall(double distance, int x_pos, double ray_angle)
{
	int wall_height;
	int y_start;
	int y_end;
	int y_pos;
	u_int32_t clr = 0x00000000; //CHANGE LATER

	y_pos = 0;
	wall_height = (int)(TILE * STD_HEIGHT / (distance * cos(ray_angle - game()->player.angle)));
	if (wall_height < 15)
		wall_height = 15;
	
	y_start = (STD_HEIGHT / 2) - (wall_height / 2);
	y_end = y_start + wall_height;
	
	while(y_pos < STD_HEIGHT)
	{
		if (y_pos < y_start)
			mlx_put_pixel(game()->img, x_pos, y_pos, game()->map->ceiling);
		else if (y_pos >= y_end)
			mlx_put_pixel(game()->img, x_pos, y_pos, game()->map->floor);
		else
			mlx_put_pixel(game()->img, x_pos, y_pos, clr);
		y_pos++;
	}
}

void render_view(void)
{
	double distance; //TODO: OPTIMIZE THIS SHIT
	double start_angle;
	double delta;
	int i = 0;
	int num_rays = STD_WIDTH;

	game()->player.angle = normalize_angle(game()->player.angle);
	start_angle = normalize_angle(game()->player.angle - (FOV / 2));
	delta = FOV / num_rays;
	while (i < num_rays)
	{
		distance = cast_ray_n_draw(game()->img, start_angle, 0x0, false);
		start_angle = normalize_angle(start_angle + delta);
		render_wall(distance, i, start_angle);
		i++;
	}
}

void render_game(void)
{
	render_view();
	// render_minimap();
	//render crosshair
}

void render_loop(void *param)
{
	(void)param;
	render_movement();
	render_game();
}

int	main_render(t_map *map)
{
	if (initialise_game(map) != 0)
		return (1);

	//========--TESTING--========//
	main_hooks();
	mlx_loop(game()->mlx);
	mlx_terminate(game()->mlx);
	//===========================//
	
	// exit funciton
	
	return (0);
}
