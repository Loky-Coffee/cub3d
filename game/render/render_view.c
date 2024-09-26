#include "../../include/cub3d.h"

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

mlx_image_t *get_wall_direction(float angle)
{
	angle = normalize_angle(angle);

	if (angle >= 0 && angle < M_PI_2) //EAST
		return (game()->tex->east_img);	
	else if (angle >= M_PI_2 && angle < PI) // SOUTH
		return (game()->tex->south_img);
	else if (angle >= PI && angle < 3 * M_PI_2) // WEST
		return (game()->tex->west_img);
	else												// NORTH
		return (game()->tex->north_img);
}

//---WHAT TO DO---//
// -- get x pos of pixel on image
// -- get y pod of pixel on image
// -- get the color
// -- put the pixel
//----------------//
void put_image(float ray_angle, int y_pos, int x_pos, int y_start, int y_end)
{
	t_game *g;
	mlx_image_t *wall;
	t_color wall_clr;
	int tex_y;
	int tex_x;
	float hit_point;

	g = game();

	wall = get_wall_direction(ray_angle);
	hit_point = get_hit_point(ray_angle);

	tex_x = (hit_point / TILE) * wall->width;

	double relative_wall_pos = (y_pos - y_start) / (float)(y_end - y_start);
	tex_y = relative_wall_pos * wall->height;
	
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)wall->height)
		tex_y = wall->height - 1;

    wall_clr = *(t_color *)(wall->pixels + (tex_y * wall->width + tex_x) * sizeof(t_color));

	mlx_put_pixel(g->img, x_pos, y_pos, wall_clr.color);
}

void render_wall(double distance, int x_pos, double ray_angle, t_game *game) 
{
	int wall_height;
	int y_start;
	int y_end;
	int y_pos;
	int height;

	height = (int)game->img->height;
	wall_height = (int)(TILE * height / (distance * cos(ray_angle - game->player.angle)));
	if (wall_height < 15)
		wall_height = 15;
	y_start = (height / 2) - (wall_height / 2);
	y_end = y_start + wall_height;
	y_pos = 0;

	while (y_pos < height)
	{
		if (y_pos < y_start)
			mlx_put_pixel(game->img, x_pos, y_pos, game->map->ceiling);
		else if (y_pos >= y_end)
			mlx_put_pixel(game->img, x_pos, y_pos, game->map->floor);
		else
			put_image(ray_angle, y_pos, x_pos, y_start, y_end);
			// mlx_put_pixel(game->img, x_pos, y_pos, 0x00000000);
		y_pos++;
	}
}

void render_view(t_game *game)
{
	double start_angle;
	double delta;
	int i;
	int num_rays;

	i = 0;
	num_rays = game->img->width;
	game->player.angle = normalize_angle(game->player.angle);
	start_angle = normalize_angle(game->player.angle - (FOV / 2));
	delta = FOV / num_rays;
	while (i < num_rays)
	{
		raycast(start_angle, game->player.pos.x, game->player.pos.y, game, &game->ray);
		render_wall(game->ray.wall_dist, i, start_angle, game);
		start_angle = normalize_angle(start_angle + delta);
		i++;
	}
}

// void render_wall(double distance, int x_pos, double ray_angle)
// {
// 	int wall_height;
// 	int y_start;
// 	int y_end;
// 	int y_pos;

// 	int tex_y;
// 	int tex_x;
// 	double tex_step;
// 	double tex_pos;

// 	wall_height = (int)(TILE * STD_HEIGHT / (distance * cos(ray_angle - game()->player.angle)));
	
// 	if (wall_height < 15)
// 		wall_height = 15;
// 	y_start = (STD_HEIGHT / 2) - (wall_height / 2);
// 	y_end = y_start + wall_height;
	
// 	tex_step = (double)game()->tex->west_img->height / wall_height;
// 	tex_pos = 0;
// 	//WEENN DER SIDE FERTIG IST KANN MAN DAS EINSCHALTEN! UND DIE KOMENTARE IN FIND_WALL EBEN SO!
// 	// if (game()->player.side == 0) {
// 	// 	tex_x = (int)(fmod(game()->player.ray_y, TILE) * find_wall()->width / TILE);
// 	// } else {
// 		tex_x = (int)(fmod(game()->player.ray_x, TILE) * find_wall()->width / TILE);
// 	// }

// 	y_pos = 0;
// 	while (y_pos < STD_HEIGHT)
// 	{
// 		if (y_pos < y_start)
// 			mlx_put_pixel(game()->img, x_pos, y_pos, game()->map->ceiling);
// 		else if (y_pos >= y_end)
// 			mlx_put_pixel(game()->img, x_pos, y_pos, game()->map->floor);
// 		else
// 		{
// 			tex_y = (int)tex_pos & (game()->tex->west_img->height - 1);
// 			tex_pos += tex_step;
// 			int i = (tex_y * game()->tex->west_img->width + tex_x) * 4;
// 			t_color color;
// 			if (i >= 0 && ((i + 3) < (int)(game()->tex->west_img->width * game()->tex->west_img->height * 4)))
// 			{//west IMAGE HARDGECODET.. muss der auswahl je nach himels richtung angepasst!!
// 				color.red = game()->tex->west_img->pixels[i];
// 				color.green = game()->tex->west_img->pixels[i + 1];
// 				color.blue = game()->tex->west_img->pixels[i + 2];
// 				color.alpha = game()->tex->west_img->pixels[i + 3];
// 			}
// 			else
// 			{
// 				color.color = game()->map->floor;
// 			}
// 			mlx_put_pixel(game()->img, x_pos, y_pos, color.color);
// 		}
// 		y_pos++;
// 	}
// }
