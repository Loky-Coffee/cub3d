/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckIdentifier_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 04:16:13 by aalatzas          #+#    #+#             */
/*   Updated: 2024/10/04 10:40:16 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d_bonus.h"

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

	y = 0;
	while (a->map && a->map[y])
	{
		if (ft_strncmp(a->map[y], "NO ", 3) == 0)
			a->map_pos.north_txt = y;
		else if (ft_strncmp(a->map[y], "SO ", 3) == 0)
			a->map_pos.south_txt = y;
		else if (ft_strncmp(a->map[y], "WE ", 3) == 0)
			a->map_pos.west_txt = y;
		else if (ft_strncmp(a->map[y], "EA ", 3) == 0)
			a->map_pos.east_txt = y;
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
