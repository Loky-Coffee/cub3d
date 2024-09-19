/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckColorsRGB.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:46:20 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/19 12:03:56 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static unsigned char	get_next_color(char **str, bool comma, unsigned char *p)
{
	unsigned char	color;
	size_t			i;

	color = 0;
	i = 0;
	while (!ft_isdigit(**str))
	{
		if (*(*str) == ',')
			comma = true;
		(*str)++;
	}
	if (comma == false)
		return (printf("ERROR: incorrect number of commas in RGB values\n"), 1);
	while (*str && **str && ft_isdigit(**str))
	{
		color = color * 10 + (*(*str) - '0');
		i++;
		(*str)++;
	}
	*p = color;
	return (0);
}

static int	convert_color_to_int(t_color *color, char *str)
{
	char	*it;

	it = str + 1;
	if (get_next_color (&it, true, &color->red) != 0)
		return (1);
	if (get_next_color (&it, false, &color->green) != 0)
		return (1);
	if (get_next_color (&it, false, &color->blue) != 0)
		return (1);
	color->alpha = 255;
	return (0);
}

static int	check_commas(const char *line)
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
		return (printf("ERROR: incorrect number of commas in RGB values\n"), 1);
	return (0);
}

// int check_color_number()
// {

// }

int	check_map_colors(t_p *a)
{
	size_t	y;

	y = 0;
	if (check_commas(a->map[a->map_pos.floor_color_pos]) != 0)
		return (1);
	if (check_commas(a->map[a->map_pos.ceiling_color_pos]) != 0)
		return (1);
	if (convert_color_to_int(&a->floor, a->map[a->map_pos.floor_color_pos]) != 0)
		return (1);
	if (convert_color_to_int(&a->ceiling, a->map[a->map_pos.ceiling_color_pos]) != 0)
		return (1);
	return (0);
}
