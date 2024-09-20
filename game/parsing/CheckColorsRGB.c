/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckColorsRGB.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:46:20 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/20 23:11:15 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned char	get_next_color(char **str, bool comma, unsigned char *p, t_p *a)
{
	int		color;
	size_t	i;

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
	return (0);
}

static int	convert_color_to_int(t_color *color, char *str, t_p *a)
{
	char	*it;

	it = str + 1;
	if (get_next_color (&it, true, &color->red, a) != 0)
		return (1);
	if (get_next_color (&it, false, &color->green, a) != 0)
		return (1);
	if (get_next_color (&it, false, &color->blue, a) != 0)
		return (1);
	color->alpha = 255;

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\ncolor->red %d\n", color->red);
	printf("color->green %d\n", color->green);
	printf("color->blue %d\n", color->blue);
	printf("color->alpha %d\n", color->alpha);
	printf("color->color %d\n", color->color);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	return (0);
}

static int	check_commas(const char *line, t_p *a)
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
	return (0);
}

int	init_colors(t_p *a)
{
	size_t	y;

	y = 0;
	if (check_commas(a->map[a->map_pos.floor_color_pos], a) != 0)
		return (1);
	if (check_commas(a->map[a->map_pos.ceiling_color_pos], a) != 0)
		return (1);
	if (convert_color_to_int(&a->floor, a->map[a->map_pos.floor_color_pos], a) != 0)
		return (1);
	if (convert_color_to_int(&a->ceiling, a->map[a->map_pos.ceiling_color_pos], a) != 0)
		return (1);
	return (0);
}
