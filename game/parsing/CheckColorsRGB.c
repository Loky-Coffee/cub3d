/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckColorsRGB.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:46:20 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/18 08:31:11 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	convert_colors_to_int(t_p *a)
{
	size_t	i;
	size_t	y;
	size_t lenght;
	// char	nbr[3];

	i = 4;
	y = 1;
	lenght = 0;
	while (i < 6)
	{
		while (a->map && a->map[i] && a->map[i][y] == ' ')
			y++;
	}
	return (0);
}
int check_rgb_value(const char *line, size_t *y, int color_count)
{
	int color_value = 0;
	size_t lenght = 0;

	while (line[*y] == ' ')
		(*y)++;
	while (ft_isdigit(line[*y]))
	{
		color_value = color_value * 10 + (line[*y] - '0');
		lenght++;
		(*y)++;
	}
	if (color_value < 0 || color_value > 255 || lenght == 0 || lenght > 3)
		return (printf("ERROR: RGB Colors must be in the range 0,0,0 to 255,255,255\n"), 1);
	while (line[*y] == ' ')
		(*y)++;
	if (color_count < 2 && line[*y] != ',')
		return (printf("ERROR: Missing comma between RGB values\n"), 1);
	if (line[*y] == ',')
		(*y)++;
	return (0);
}

int check_map_colors(t_p *a)
{
	size_t i = 4;
	size_t y;
	int color_count;

	while (i < 6)
	{
		y = 1;
		color_count = 0;
		while (a->map && a->map[i] && a->map[i][y] == ' ')
			y++;
		while (color_count < 3)
		{
			if (check_rgb_value(a->map[i], &y, color_count) == 1)
				return (1);
			color_count++;
		}
		i++;
	}
	convert_colors_to_int(a);
	return (0);
}
