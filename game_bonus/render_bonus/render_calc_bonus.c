#include "../../include_bonus/cub3d_bonus.h"

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

void wait_for_fps(void)
{
	static struct timeval last_time;
	struct timeval curr_time;
	long elapsed_time;

	gettimeofday(&curr_time, NULL);
	elapsed_time = (curr_time.tv_sec - last_time.tv_sec) * 1000000 + 
			(curr_time.tv_usec - last_time.tv_usec);
	if (elapsed_time < FRAME_TIME)
		usleep(FRAME_TIME - elapsed_time - 3);
	gettimeofday(&last_time, NULL);
}