#include "../../include/cub3d.h"

int wall_colission(float x, float y)
{
	int map_x;
	int map_y;

	map_x = (int)x / TILE;
	map_y = (int)y / TILE;
	if ((map_x >= 0) && (map_x < game()->map->map_width) && (map_y >= 0) && map_y < game()->map->map_height)
		return(game()->map->map[map_y][map_x] == '1');
	return (1);
}

// vielleicht radar stufen einbauen durch integer der sich inkrementiert
// und dann so halbkreise zieht
float cast_ray_n_draw(mlx_image_t *img, float ray_angle, int clr, bool draw)
{
	float ray_x;
	float ray_y;
	float ray_dx;
	float ray_dy;
	float distance;

	ray_x = game()->player.pos.x;
	ray_y = game()->player.pos.y;
	ray_dx = cos(ray_angle);
	ray_dy = sin(ray_angle);
	while (!wall_colission(ray_x, ray_y))
	{
		ray_x += ray_dx;
		ray_y += ray_dy;
		if (draw)
			mlx_put_pixel(img, (u_int32_t)10 + ray_x * MAP_SCALE, (u_int32_t)10 + ray_y * MAP_SCALE, clr);
	}
	distance = sqrt(pow(ray_x - game()->player.pos.x, 2) + pow(ray_y - game()->player.pos.y, 2));
	game()->player.ray_x = ray_x;
	game()->player.ray_y = ray_y;
	return distance;
}

void raycast(float ray_angle, float play_x, float play_y, t_game *game, t_ray *ray)
{
	float d_dist_x;
	float d_dist_y;
	// um zu bestimmen ob der strahl jeweils nach links - rechts(X) oder oben - unten(Y) geht
	
	float step_x;
	float step_y;
	
	// distanz zum naechstem hit am kaestchen
	float side_dist_x;
	float side_dist_y;
	
	// dadurch bekommen wir die richtung in der die rays zielen
	ray->ray_dir_x = cos(ray_angle);
	ray->ray_dir_y = sin(ray_angle);
	
	ray->map_x = (int)floor(game->player.pos.x);
	ray->map_y = (int)floor(game->player.pos.y);
	// distance zum nachsten hit am kaestchen
	d_dist_x = fabs(1 / ray->ray_dir_x);
	d_dist_y = fabs(1 / ray->ray_dir_y);

	if (ray->ray_dir_x < 0) // wenn negativ dann zeigt ray nach links also -1
	{
		step_x = -1;
		side_dist_x = (play_x - ray->map_x) * d_dist_x;
	}
	else					// ansonsten 1 weil es in die positive richtung berechnet werden muss
	{
		step_x = 1;
		side_dist_x = (ray->map_x + 1.0 - play_x) * d_dist_x;
	}

	if (ray->ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (play_y - ray->map_y) * d_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (ray->map_y + 1.0 - play_y) * d_dist_y;
	}
	
	//- - - - - - - CUT - HERE - - - - - - -//

	while (true)
	{
		if(side_dist_x < side_dist_y) // wenn der abstand zum nachsten x hit kleiner ist als y wird dieser zuerst berechnet
		{
			side_dist_x += d_dist_x;
			ray->map_x += step_x;
			ray->is_horizontal = 0;
		}
		else
		{
			side_dist_y += d_dist_y;
			ray->map_y += step_y;
			ray->is_horizontal = 1;
		}
		if (wall_colission(ray->map_x, ray->map_y))
			break;
	}

	//- - - - - - - CUT - HERE - - - - - - -//
	
// calculate the wall distance depending on which wall was hit
	if (ray->is_horizontal == 0)
		ray->wall_dist = ((float)ray->map_x - play_x + (1 - step_x) / 2) / ray->ray_dir_x;
	else
		ray->wall_dist = ((float)ray->map_y - play_y + (1 - step_y) / 2) / ray->ray_dir_y;
// calculate the hit points of the ray
	ray->ray_x = play_x + ray->wall_dist * ray->ray_dir_x;
	ray->ray_y = play_y + ray->wall_dist * ray->ray_dir_y;
}
