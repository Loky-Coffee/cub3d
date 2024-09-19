/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:47:14 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/19 23:42:20 by aalatzas         ###   ########.fr       */
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
static bool search(int x, int y, char **map, bool *map_not_valid, int map_height)
{
	if (y < 0 || y >= map_height || x < 0 || x >= (int)strlen(map[y]))
	{
		*map_not_valid = true;
		return false;
	}
	char current_char = map[y][x];
	if (current_char == '1' || current_char == 'V')
		return true;
	if (current_char == ' ')
	{
		*map_not_valid = true;
		return false;
	}
	if (current_char == '0')
		map[y][x] = '!';
	map[y][x] = 'V';
	if (!search(x + 1, y, map, map_not_valid, map_height))
		return false;
	if (!search(x - 1, y, map, map_not_valid, map_height))
		return false;
	if (!search(x, y - 1, map, map_not_valid, map_height))
		return false;
	if (!search(x, y + 1, map, map_not_valid, map_height))
		return false;
	return true;
}

void	search_utils(t_p *a)
{
	int i;
	int x;
	char **buff;
	bool map_not_valid = false;
	bool result;

	i = 0;
	while (a->map[i])
		i++;
	buff = malloc(sizeof(char *) * (i + 1));
	x = 0;
	while (x < i)
	{
		buff[x] = ft_strdup(a->map[x]);
		x++;
	}
	buff[i] = NULL;

	result = search(a->map_pos.player_x, a->map_pos.player_y, buff, &map_not_valid, i);
	if (map_not_valid || !result)
		error_exit(a, "ERROR: Map ist nicht Valid!!\n", 1);
}


void	find_map_start(t_p *a)
{
	int		y;
	bool	start_find;

	y = 0;
	start_find = false;
	while (a->map[y])
	{
		if (y == a->map_pos.ceiling_color_pos || y == a->map_pos.east_txt || \
		y == a->map_pos.floor_color_pos || y == a->map_pos.north_txt || \
		y == a->map_pos.south_txt || y == a->map_pos.west_txt)
		{
			y++;
			continue;
		}
		if (ft_isspace(*a->map[y]) == 1 || *a->map[y] == '1' || *a->map[y] == '0')
		{
			if (start_find == false)
			{
				start_find = true;
				a->map_pos.map_pos_start = y;
			}
			a->map_pos.map_pos_end = y;
		}
		y++;
	}
}
