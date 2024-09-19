/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckIdentifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 04:16:13 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/19 09:45:09 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int check_color_pos(t_p *a)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while (a->map && a->map[y])
	{
		while(a->map && a->map[y] && a->map[y][i] != '\0')
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
		return (printf("ERROR: Map aquments are not correct!"), 1);

	return (0);
}

static int check_texture_pos(t_p *a)
{
	int i;
	int y;
	int nbr;

	i = 0;
	y = 0;
	nbr = 0;
	while (a->map && a->map[y])
	{
		while(a->map && a->map[y] && a->map[y][i] != '\0')
		{
			if (a->map[y][i] == 'O' && a->map[y][i - 1] == 'N')
				a->map_pos.north_txt = y;
			else if (a->map[y][i] == 'O' && a->map[y][i - 1] == 'S')
				a->map_pos.south_txt = y;
			else if (a->map[y][i] == 'E' && a->map[y][i - 1] == 'W')
				a->map_pos.west_txt = y;
			else if (a->map[y][i] == 'A' && a->map[y][i - 1] == 'E')
				a->map_pos.east_txt = y;
			else if (a->map[y][i] == 'F')
				a->map_pos.floor_color_pos = y;
			else if (a->map[y][i] == 'C')
				a->map_pos.ceiling_color_pos = y;
			i++;
		}
		i = 0;
		y++;
	}
	if (a->map_pos.north_txt == -1 || a->map_pos.south_txt == -1 || \
	a->map_pos.west_txt == -1 || a->map_pos.east_txt == -1)
		return (printf("ERROR: Map aquments are not correct!"), 1);

	return (0);
}

int	check_map_identifier(t_p *a)
{
	size_t i;

	i = 0;
	// while (a->map[i])
	// {
	// 	if (i == 0 && !(ft_strncmp(a->map[i], "NO ", 3) == 0))
	// 		return (printf("ERROR:\n north Identifier must be NO"), 1);
	// 	else if (i == 1 && !(ft_strncmp(a->map[i], "SO ", 3) == 0))
	// 		return (printf("ERROR:\n south Identifier must be SO"), 1);
	// 	else if (i == 2 && !(ft_strncmp(a->map[i], "WE ", 3) == 0))
	// 		return (printf("ERROR:\n west Identifier must be WE"), 1);
	// 	else if (i == 3 && !(ft_strncmp(a->map[i], "EA ", 3) == 0))
	// 		return (printf("ERROR:\n east Identifier must be EA"), 1);
	// 	else if (i == 4 && !(ft_strncmp(a->map[i], "F ", 2) == 0))
	// 		return (printf("ERROR:\n Floor color Identifier must be F"), 1);
	// 	else if (i == 5 && !(ft_strncmp(a->map[i], "C ", 2) == 0))
	// 		return (printf("ERROR:\n Ceiling color Identifier must be C"), 1);
	// 	i++;
	// }
	if(check_texture_pos(a) != 0)
		return (EXIT_FAILURE);
	if(check_color_pos(a) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
