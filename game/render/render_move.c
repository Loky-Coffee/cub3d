/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:30:43 by csteudin          #+#    #+#             */
/*   Updated: 2024/10/10 10:53:56 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vec_2	get_next_pos(t_vec_2 pos, t_move mode)
{
	t_vec_2	new_pos;

	new_pos.x = 0;
	new_pos.y = 0;
	if (mode == MOV_UP)
	{
		new_pos.x = pos.x + cos(game()->player.angle) * SPEED;
		new_pos.y = pos.y + sin(game()->player.angle) * SPEED;
	}
	else if (mode == MOV_DOWN)
	{
		new_pos.x = pos.x - cos(game()->player.angle) * SPEED;
		new_pos.y = pos.y - sin(game()->player.angle) * SPEED;
	}
	else if (mode == MOV_LEFT)
	{
		new_pos.x = pos.x - cos(game()->player.angle + PI / 2) * SPEED;
		new_pos.y = pos.y - sin(game()->player.angle + PI / 2) * SPEED;
	}
	else if (mode == MOV_RIGHT)
	{
		new_pos.x = pos.x + cos(game()->player.angle + PI / 2) * SPEED;
		new_pos.y = pos.y + sin(game()->player.angle + PI / 2) * SPEED;
	}
	return (new_pos);
}

void	move(t_vec_2 new_pos)
{
	if (!wall_colission(new_pos.x, new_pos.y))
	{
		game()->player.pos.x = new_pos.x;
		game()->player.pos.y = new_pos.y;
	}
}

void	look(t_game *g)
{
	if (g->player.look_right)
		g->player.angle += 0.10;
	else if (g->player.look_left)
		g->player.angle -= 0.10;
	g->player.angle = normalize_angle(g->player.angle);
}

/*
 *	> cosinus is for calculating how much movement is on the X
 *	> sinus is for how much on the y
 *	> then just multiply it with the speed and the you got your new position
 */
void	render_movement(void)
{
	t_game	*g;
	t_vec_2	new_pos;

	g = game();
	look(g);
	if (g->player.move_up)
	{
		new_pos = get_next_pos(g->player.pos, MOV_UP);
		move(new_pos);
	}
	if (g->player.move_down)
	{
		new_pos = get_next_pos(g->player.pos, MOV_DOWN);
		move(new_pos);
	}
	if (g->player.move_left)
	{
		new_pos = get_next_pos(g->player.pos, MOV_LEFT);
		move(new_pos);
	}
	if (g->player.move_right)
	{
		new_pos = get_next_pos(g->player.pos, MOV_RIGHT);
		move(new_pos);
	}
}

int	wall_colission(float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x / TILE;
	map_y = (int)y / TILE;
	if ((map_x >= 0) && (map_x < game()->map->map_width) && (map_y >= 0)
		&& map_y < game()->map->map_height)
		return (game()->map->map[map_y][map_x] == '1');
	return (1);
}
