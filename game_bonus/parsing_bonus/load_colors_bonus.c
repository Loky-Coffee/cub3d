/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_colors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:46:20 by aalatzas          #+#    #+#             */
/*   Updated: 2024/10/04 13:26:46 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d_bonus.h"

static void	get_next_color(char **str, bool comma, unsigned char *p, t_p *a)
{
	uint8_t		color;
	size_t		i;

	color = 0;
	i = 0;
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
		i++;
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
	get_next_color (&it, true, &color->red, a);
	get_next_color (&it, false, &color->green, a);
	get_next_color (&it, false, &color->blue, a);
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
