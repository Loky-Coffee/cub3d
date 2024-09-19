/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:47:14 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/19 21:07:39 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



void find_map_start(t_p *a)
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
