/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckIdentifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 04:16:13 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/21 01:55:59 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	check_color_pos(t_p *a)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (a->map && a->map[y])
	{
		while (a->map && a->map[y] && a->map[y][i] != '\0')
		{
			if (a->map[y][i] == 'F')
				a->map_pos.floor_color_pos = y;
			else if (a->map[y][i] == 'C')
				a->map_pos.ceiling_color_pos = y;
			i++;
		}
		i = 0;
		y++;
	}
	if (a->map_pos.floor_color_pos == -1 || a->map_pos.ceiling_color_pos == -1)
		error_exit(a, "ERROR: Map aquments are not correct!", 1);
}

static void	check_texture_pos(t_p *a)
{
	int	y;
	int	i;

	y = 0;
	while (a->map && a->map[y])
	{
		i = 0;
		while (a->map && a->map[y] && a->map[y][i] != '\0')
		{
			if (a->map[y][i] == 'O' && a->map[y][i - 1] == 'N')
				a->map_pos.north_txt = y;
			else if (a->map[y][i] == 'O' && a->map[y][i - 1] == 'S')
				a->map_pos.south_txt = y;
			else if (a->map[y][i] == 'E' && a->map[y][i - 1] == 'W')
				a->map_pos.west_txt = y;
			else if (a->map[y][i] == 'A' && a->map[y][i - 1] == 'E')
				a->map_pos.east_txt = y;
			i++;
		}
		y++;
	}
	if (a->map_pos.north_txt == -1 || a->map_pos.south_txt == -1 || \
	a->map_pos.west_txt == -1 || a->map_pos.east_txt == -1)
		error_exit(a, "ERROR: Map aquments are not correct!", 1);
}

void	check_map_identifier(t_p *a)
{
	check_texture_pos(a);
	check_color_pos(a);
}
