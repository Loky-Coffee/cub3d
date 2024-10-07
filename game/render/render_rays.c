/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 04:23:44 by csteudin          #+#    #+#             */
/*   Updated: 2024/10/07 06:41:51 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calculate_step_and_side_dist(t_ray *ray, t_vec_2 *step,
		t_vec_2 *side_dist, t_vec_2 d_dist)
{
	t_vec_2	player_pos;

	player_pos = game()->player.pos;
	if (ray->ray_dir_x < 0)
	{
		step->x = -1;
		side_dist->x = (player_pos.x - ray->map_x) * d_dist.x;
	}
	else
	{
		step->x = 1;
		side_dist->x = (ray->map_x + 1.0 - player_pos.x) * d_dist.x;
	}
	if (ray->ray_dir_y < 0)
	{
		step->y = -1;
		side_dist->y = (player_pos.y - ray->map_y) * d_dist.y;
	}
	else
	{
		step->y = 1;
		side_dist->y = (ray->map_y + 1.0 - player_pos.y) * d_dist.y;
	}
}

void	perform_dda(t_vec_2 *side_dist, t_vec_2 *d_dist, t_vec_2 *step,
		t_ray *ray)
{
	while (true)
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += d_dist->x;
			ray->map_x += step->x;
			ray->is_horizontal = 0;
		}
		else
		{
			side_dist->y += d_dist->y;
			ray->map_y += step->y;
			ray->is_horizontal = 1;
		}
		if (wall_colission((float)ray->map_x, (float)ray->map_y))
			break ;
	}
}

void	calculate_wall_dist_and_hit(t_vec_2 player_pos, t_ray *ray,
		t_vec_2 step)
{
	if (ray->is_horizontal == 0)
		ray->wall_dist = ((float)ray->map_x - player_pos.x + (1 - step.x) / 2)
			/ ray->ray_dir_x;
	else
		ray->wall_dist = ((float)ray->map_y - player_pos.y + (1 - step.y) / 2)
			/ ray->ray_dir_y;
	ray->ray_x = player_pos.x + ray->wall_dist * ray->ray_dir_x;
	ray->ray_y = player_pos.y + ray->wall_dist * ray->ray_dir_y;
}

void	raycast(float ray_angle, t_vec_2 player_pos, t_game *game, t_ray *ray)
{
	t_vec_2	d_dist;
	t_vec_2	step;
	t_vec_2	side_dist;

	ray->ray_dir_x = cos(ray_angle);
	ray->ray_dir_y = sin(ray_angle);
	ray->map_x = (int)floor(game->player.pos.x);
	ray->map_y = (int)floor(game->player.pos.y);
	d_dist.x = fabs(1 / ray->ray_dir_x);
	d_dist.y = fabs(1 / ray->ray_dir_y);
	calculate_step_and_side_dist(ray, &step, &side_dist, d_dist);
	perform_dda(&side_dist, &d_dist, &step, ray);
	calculate_wall_dist_and_hit(player_pos, ray, step);
}
