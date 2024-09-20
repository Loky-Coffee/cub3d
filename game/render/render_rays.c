#include "../../include/cub3d.h"

int wall_colission(double x, double y)
{
	int map_x;
	int map_y;

	map_x = (int)x / TILE;
	map_y = (int)y / TILE;
	if ((map_x >= 0) && (map_x < game()->map->map_width) && (map_y >= 0) && map_y < game()->map->map_height) //TODO: 12 and 6 | width and height of the map 
		return(game()->map->map[map_y][map_x] == '1');
	return (1);
}

void cast_ray_n_draw(mlx_image_t *img, double ray_angle, t_color clr, bool draw)
{
	double ray_x;
	double ray_y;
	double ray_dx;
	double ray_dy;

	ray_x = game()->player.pos.x;
	ray_y = game()->player.pos.y;
	ray_dx = cos(ray_angle);
	ray_dy = sin(ray_angle);
	while(!wall_colission(ray_x, ray_y))
	{
		ray_x += ray_dx;
		ray_y += ray_dy;
		if (draw)
			mlx_put_pixel(img, (u_int32_t)ray_x, (u_int32_t)ray_y, clr.color);
	}
}
