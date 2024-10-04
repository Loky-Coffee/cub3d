/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data_on_stack_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:24:45 by aalatzas          #+#    #+#             */
/*   Updated: 2024/10/04 10:40:30 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d_bonus.h"

void	erase_oldmap(t_p *a)
{
	int	oldpos;
	int	newpos;

	oldpos = a->map_pos.map_pos_start;
	newpos = 0;
	while (oldpos <= a->map_pos.map_pos_end)
	{
		a->map[newpos] = a->map[oldpos];
		newpos++;
		oldpos++;
	}
	a->map[newpos] = NULL;
}

static void	load_map_on_stack(t_p *src, t_map *dest)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (src->map[i])
		i++;
	while (src->map[x])
	{
		if (!dest->map)
			dest->map = malloc(sizeof(char *) * (i + 1));
		dest->map[x] = ft_strdup(src->map[x]);
		x++;
	}
	dest->map[i] = NULL;
	if (src->map)
		free_split(src->map);
}

int	load_data_on_stack(t_p *src, t_map *dest)
{
	dest->ceiling = src->ceiling.color;
	dest->floor = src->floor.color;
	dest->player_pos_x = src->map_pos.player_x;
	dest->player_pos_y = src->map_pos.player_y;
	ft_strlcpy(dest->east_texture, src->east_texture, \
	sizeof(src->east_texture));
	ft_strlcpy(dest->north_texture, src->north_texture, \
	sizeof(src->north_texture));
	ft_strlcpy(dest->south_texture, src->south_texture, \
	sizeof(src->south_texture));
	ft_strlcpy(dest->west_texture, src->west_texture, \
	sizeof(src->west_texture));
	ft_strlcpy(dest->map_name, src->map_name, sizeof(src->map_name));
	load_map_on_stack(src, dest);
	return (0);
}
