#include "../../include_bonus/cub3d_bonus.h"

mlx_image_t *get_wall_direction(t_ray *ray)
{
	if (ray->is_horizontal == 1)
	{
		if (ray->ray_dir_y > 0)
			return (game()->tex->north_img);
		else
			return (game()->tex->south_img);
	}
	else
	{
		if (ray->ray_dir_x > 0)
			return (game()->tex->east_img);
		else
			return (game()->tex->west_img);
	}
}

uint32_t argb_to_rgba(t_color color)
{
	return ((color.red << 16) | (color.green << 8) | color.blue | (color.alpha << 24));
}

//---WHAT TO DO---//
// -- get x pos of pixel on image
// -- get y pod of pixel on image
// -- get the color
// -- put the pixel
//----------------//
void put_image(int y_pos, int x_pos, int y_start, int y_end, t_game *g)
{
	t_ray *ray;
	mlx_image_t *wall;
	float relative_wall_pos;
	float hit_point;
	t_vec_2_int tex;
	
	ray = &game()->ray;
	wall = get_wall_direction(ray);
	relative_wall_pos = (float)(y_pos - y_start) / (y_end - y_start);	
	if (ray->is_horizontal)
		hit_point = ray->ray_x;
	else
		hit_point = ray->ray_y;
	tex.x = (int)(hit_point / TILE * wall->width) % wall->width;
	if (tex.x < 0)
		tex.x = 0;
	if (tex.x >= wall->width)
		tex.x = wall->width - 1;
	tex.y = (int)(relative_wall_pos * wall->height);
	if (tex.y < 0)
		tex.y = 0;
	if (tex.y >= wall->height)
		tex.y = wall->height - 1;
	mlx_put_pixel(g->img, x_pos, y_pos, argb_to_rgba(*(t_color *)\
		(wall->pixels + (tex.y * wall->width + tex.x) * sizeof(uint32_t))));
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
			put_image(y_pos, x_pos, y_start, y_end, game);
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