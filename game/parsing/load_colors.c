/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:46:20 by aalatzas          #+#    #+#             */
/*   Updated: 2024/10/10 11:26:34 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	get_next_color(char **str, bool comma, unsigned char *p, t_p *a)
{
	uint8_t		color;

	color = 0;
	while (!ft_isdigit(**str))
	{
		if (*(*str) == ',')
			comma = true;
		(*str)++;
	}
	if (comma == false)
		error_exit(a, "ERROR: incorrect number of commas in RGB values", 1);
	while (*str && **str && ft_isdigit(**str))
	{
		color = color * 10 + (**str - '0');
		(*str)++;
	}
	if (color < 0 || color > 255)
		error_exit(a, "ERROR: Colors must be between 0-255", 1);
	*p = (unsigned char)color;
}

static void	convert_color_to_int(t_color *color, char *str, t_p *a)
{
	char	*it;

	it = str + 1;
	get_next_color (&it, true, &color->blue, a);
	get_next_color (&it, false, &color->green, a);
	get_next_color (&it, false, &color->red, a);
	color->alpha = 255;
}

static void	check_commas(const char *line, t_p *a)
{
	int	count;
	int	y;

	count = 0;
	y = 0;
	while (line[y])
	{
		if (line[y] == ',')
			count++;
		y++;
	}
	if (count != 2)
		error_exit(a, "ERROR: incorrect number of commas in RGB values", 1);
}

void	load_colors(t_p *a)
{
	check_commas(a->map[a->map_pos.floor_color_pos], a);
	check_commas(a->map[a->map_pos.ceiling_color_pos], a);
	convert_color_to_int(&a->floor, a->map[a->map_pos.floor_color_pos], a);
	convert_color_to_int(&a->ceiling, a->map[a->map_pos.ceiling_color_pos], a);
}
