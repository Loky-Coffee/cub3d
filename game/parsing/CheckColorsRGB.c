/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckColorsRGB.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:46:20 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/18 07:48:47 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	convert_colors_to_int(t_p *a)
{
	size_t	i;
	size_t	y;
	size_t lenght;
	// char	*nbr;

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

int check_map_colors(t_p *a)
{
	size_t	i;
	size_t	y;

	i = 4;
	y = 1;
	while (i < 6)
	{
		while (a->map && a->map[i] && a->map[i][y] == ' ')
			y++;
		while (a->map[i][y] != '\0')
		{
			if(a->map[i][y] == ',')
				y++;
			while (a->map[i][y] == ' ' && a->map[i][y] != '\0')
				y++;
			if (a->map[i][y] != '\0' && ft_isdigit(a->map[i][y]) == 0)
				return (printf("ERROR: RGB Collors must be min:0,0,0 max:255,255,255"), 1);
			y++;
		}
		i++;
	}
	return (0);
}
