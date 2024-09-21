/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:47:14 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/21 01:40:01 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	find_char_position(t_p *a)
{
	int		x;
	int		y;
	bool	find;

	y = 0;
	find = false;
	while (a->map[y])
	{
		x = 0;
		while (a->map[y][x] != '\0')
		{
			if (ft_strchr("NSWE", a->map[y][x]))
			{
				if (find == true)
					error_exit(a, "ERROR: Only one char ist allower\n", 1);
				find = true;
				a->map_pos.player_x = x;
				a->map_pos.player_y = y;
			}
			x++;
		}
		y++;
	}
}

static bool	search(int x, int y, int map_height, t_p *a)
{
	char	current_char;

	if (y < 0 || y >= map_height || x < 0 || x >= (int)strlen(a->buff_map[y]))
	{
		a->map_not_valid = true;
		return (false);
	}
	current_char = a->buff_map[y][x];
	if (current_char == '1' || current_char == 'V')
		return (true);
	else if (current_char == ' ')
	{
		a->map_not_valid = true;
		return (false);
	}
	else if (current_char == '0')
		a->buff_map[y][x] = '!';
	else
		a->buff_map[y][x] = 'V';
	if (!search(x + 1, y, map_height, a) || !search(x - 1, y, map_height, a) || \
		!search(x, y - 1, map_height, a) || !search(x, y + 1, map_height, a))
		return (false);
	return (true);
}

void	search_utils(t_p *a)
{
	int		i;
	int		x;
	bool	result;

	i = 0;
	while (a->map[i])
		i++;
	a->buff_map = malloc(sizeof(char *) * (i + 1));
	x = 0;
	while (x < i)
	{
		a->buff_map[x] = ft_strdup(a->map[x]);
		x++;
	}
	a->buff_map[i] = NULL;
	result = search(a->map_pos.player_x, a->map_pos.player_y, i, a);
	if (a->map_not_valid || !result)
		error_exit(a, "ERROR: Map ist nicht Valid!!\n", 1);
}

void	find_map_start(t_p *a)
{
	int		y;

	y = 0;
	a->start_find = false;
	while (a->map[y])
	{
		if (y == a->map_pos.ceiling_color_pos || y == a->map_pos.east_txt || \
		y == a->map_pos.floor_color_pos || y == a->map_pos.north_txt || \
		y == a->map_pos.south_txt || y == a->map_pos.west_txt)
		{
			y++;
			continue ;
		}
		if (ft_isspace(*a->map[y]) == 1 \
		|| *a->map[y] == '1' || *a->map[y] == '0')
		{
			if (a->start_find == false)
			{
				a->start_find = true;
				a->map_pos.map_pos_start = y;
			}
			a->map_pos.map_pos_end = y;
		}
		y++;
	}
}
