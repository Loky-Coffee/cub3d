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

int load_textures(void)
{
	int scale_factor = STD_WIDTH / STD_HEIGHT;
	int texture_size = TILE * scale_factor * 4;
	game()->tex->north = mlx_load_png(game()->map->north_texture);
	game()->tex->south = mlx_load_png(game()->map->south_texture);
	game()->tex->east = mlx_load_png(game()->map->east_texture);
	game()->tex->west = mlx_load_png(game()->map->west_texture);
	if (game()->tex->south == NULL || game()->tex->east == NULL || game()->tex->west == NULL) {
		fprintf(stderr, "Fehler: Konnte eine oder mehrere Texturen nicht laden\n");
		return 1;
	}
	printf("game()->mlx: %p\n", game()->mlx);
	printf("game()->tex->north: %p\n", game()->tex->north);
	printf("game()->tex->south: %p\n", game()->tex->south);
	printf("game()->tex->east: %p\n", game()->tex->east);
	printf("game()->tex->west: %p\n", game()->tex->west);
	game()->tex->north_img = mlx_texture_to_image(game()->mlx, game()->tex->north);
	game()->tex->south_img = mlx_texture_to_image(game()->mlx, game()->tex->south);
	game()->tex->east_img = mlx_texture_to_image(game()->mlx, game()->tex->east);
	game()->tex->west_img = mlx_texture_to_image(game()->mlx, game()->tex->west);
	if (game()->tex->north_img == NULL || game()->tex->south_img == NULL ||
		game()->tex->east_img == NULL || game()->tex->west_img == NULL) {
		fprintf(stderr, "Fehler: Konnte ein oder mehrere Bilder nicht konvertieren\n");
		return 1;
	}
	mlx_delete_texture(game()->tex->north);
	mlx_delete_texture(game()->tex->south);
	mlx_delete_texture(game()->tex->east);
	mlx_delete_texture(game()->tex->west);
	if (mlx_resize_image(game()->tex->north_img, texture_size, texture_size) == false ||
		mlx_resize_image(game()->tex->south_img, texture_size, texture_size) == false ||
		mlx_resize_image(game()->tex->east_img, texture_size, texture_size) == false ||
		mlx_resize_image(game()->tex->west_img, texture_size, texture_size) == false) {
		fprintf(stderr, "Fehler: Konnte die Größe eines oder mehrerer Bilder nicht ändern\n");
		return 1;
	}
	return 0;
}

// void render_minimap(void)
// {
// 	t_color clr;
// 	double start_angle;
// 	double delta;
// 	int x;
// 	int num_rays = STD_WIDTH;
// 	int i = 0;

// 	x = 4;
// 	clr.color = 0x00FF00FF;

// 	clear_image(game()->img);

// 	ren_draw_table(game()->img, game()->map->map,  game()->map->map_height / 30, game()->map->map_width / 30);

// 	while(x != 0)
// 		ren_draw_circle(game()->img, game()->player.pos.x, game()->player.pos.y, x--, clr.color);

// 	game()->player.angle = normalize_angle(game()->player.angle);
// 	start_angle = normalize_angle(game()->player.angle - FOV / 2);
// 	delta = FOV / num_rays;
// 	while (i < num_rays)
// 	{
// 		cast_ray_n_draw(game()->img, start_angle, clr.color, true);
// 		start_angle = normalize_angle(start_angle + delta);
// 		i++;
// 	}
// }

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
		game()->player.angle += 0.20;
	else if (game()->player.look_left)
		game()->player.angle -= 0.20;
	game()->player.angle = normalize_angle(game()->player.angle);
}

//wir brauche die information in welche seite schaut der player damit wir die verschidene maps
//zeichen konnen....
mlx_image_t *find_wall()
{
	static mlx_image_t *current_texture;
	// if (game()->player.side == 0)
	// {
		if (game()->player.ray_x > game()->player.pos.x)
			current_texture = game()->tex->east_img;
		else
			current_texture = game()->tex->west_img;
	// }
	// else
	// {
	// 	if (game()->player.ray_y > game()->player.pos.y)
	// 		current_texture = game()->tex->south_img;
	// 	else
	// 		current_texture = game()->tex->north_img;
	// }
	return (current_texture);
}

void render_wall(double distance, int x_pos, double ray_angle)
{
	int wall_height;
	int y_start;
	int y_end;
	int y_pos;
	int tex_y;
	int tex_x;
	double tex_step;
	double tex_pos;

	wall_height = (int)(TILE * STD_HEIGHT / (distance * cos(ray_angle - game()->player.angle)));
	if (wall_height < 15) wall_height = 15;
	y_start = (STD_HEIGHT / 2) - (wall_height / 2);
	y_end = y_start + wall_height;
	tex_step = (double)game()->tex->west_img->height / wall_height;
	tex_pos = 0;
	//WEENN DER SIDE FERTIG IST KANN MAN DAS EINSCHALTEN! UND DIE KOMENTARE IN FIND_WALL EBEN SO!
	// if (game()->player.side == 0) {
	// 	tex_x = (int)(fmod(game()->player.ray_y, TILE) * find_wall()->width / TILE);
	// } else {
		tex_x = (int)(fmod(game()->player.ray_x, TILE) * find_wall()->width / TILE);
	// }

	y_pos = 0;
	while (y_pos < STD_HEIGHT)
	{
		if (y_pos < y_start)
			mlx_put_pixel(game()->img, x_pos, y_pos, game()->map->ceiling);
		else if (y_pos >= y_end)
			mlx_put_pixel(game()->img, x_pos, y_pos, game()->map->floor);
		else
		{
			tex_y = (int)tex_pos & (game()->tex->west_img->height - 1);
			tex_pos += tex_step;
			int i = (tex_y * game()->tex->west_img->width + tex_x) * 4;
			t_color color;
			if (i >= 0 && ((i + 3) < (int)(game()->tex->west_img->width * game()->tex->west_img->height * 4)))
			{//west IMAGE HARDGECODET.. muss der auswahl je nach himels richtung angepasst!!
				color.red = game()->tex->west_img->pixels[i];
				color.green = game()->tex->west_img->pixels[i + 1];
				color.blue = game()->tex->west_img->pixels[i + 2];
				color.alpha = game()->tex->west_img->pixels[i + 3];
			} else {
				color.color = game()->map->floor;
			}
			mlx_put_pixel(game()->img, x_pos, y_pos, color.color);
		}
		y_pos++;
	}
}

void render_view(void)
{
	double distance;
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
	load_textures();

	mlx_loop(game()->mlx);
	mlx_terminate(game()->mlx);
	//===========================//

	// exit funciton

	return (0);
}
