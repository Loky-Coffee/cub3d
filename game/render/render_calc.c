#include "../../include/cub3d.h"

float normalize_angle(float angle)
{
	while (angle < 0)
		angle += RA;
	while (angle >= RA)
		angle -= RA;
	return angle;
}

float get_start_angle(char direction)
{
	if (direction == 'N')
		return (3 * M_PI_2);
	else if (direction == 'E')
		return (0.00);
	else if (direction == 'S')
		return (M_PI_2);	
	else
		return (M_PI);
}

bool hit_is_vertical(float angle)
{
	if (angle < M_PI_2 && angle > 3 * M_PI_2)
		return (1);
	else
		return (0);
}

float get_hit_point(float ray_angle)
{
	if (hit_is_vertical(ray_angle))
		return (fmod(game()->player.ray_y, TILE));
	else
		return (fmod(game()->player.ray_x, TILE));
}
