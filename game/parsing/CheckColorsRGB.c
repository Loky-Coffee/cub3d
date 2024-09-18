/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckColorsRGB.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:46:20 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/18 17:09:57 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static unsigned char get_next_color(char **str)
{
	unsigned char color;
	size_t i;

	color = 0;
	i = 0;
	while (!ft_isdigit(**str))
		(*str)++;
	while (*str && **str && ft_isdigit(**str))
	{
		color = color * 10 + (*(*str) - '0');
		i++;
		(*str)++;
	}
	if (i > 3)
	{
		printf("only 3 digits allowed on colors\n");
		exit (EXIT_FAILURE);
	}
	return (color);
}

int convert_color_to_int(t_color *color, char *str)
{
	char *it;

	it = str + 1;
	color->red = get_next_color(&it);
	color->green = get_next_color(&it);
	color->blue = get_next_color(&it);
	color->alpha = 255;
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
		return (printf("ERROR: RGB out of range 0,0,0 to 255,255,255\n"), 1);
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

	// printf("HEY\n");
	// fflush(stdout);
	while (i < 6)
	{
		y = 1;
		color_count = 0;
		while (a->map && a->map[i] && ft_isspace(a->map[i][y]) != 0)
			y++;
		while (color_count < 3)
		{
			if (check_rgb_value(a->map[i], &y, color_count) == 1)
				return (1);
			color_count++;
		}
		i++;
	}
	convert_color_to_int(&a->floor, a->map[4]);
	convert_color_to_int(&a->ceiling, a->map[5]);
	return (0);
}
