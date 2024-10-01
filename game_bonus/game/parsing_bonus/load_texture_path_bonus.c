/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckTexturePath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:48:47 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/21 01:57:27 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	copy_texture_path(t_p *a, int i, char *str)
{
	size_t	y;

	y = 0;
	while (a->map[i][y] != ' ' && a->map[i][y] != '\0')
		y++;
	while (a->map[i][y] == ' ')
		y++;
	strncpy(str, &a->map[i][y], MAX_PATH_LENGTH);
	a->map_fd = open(str, O_RDONLY);
	if (a->map_fd == -1)
	{
		printf("%s: No such file or directory\n", str);
		error_exit(a, "ERROR: Map Texture aquments are not correct!", 1);
	}
	close(a->map_fd);
	i++;
}

void	load_texture_path(t_p *a)
{
	copy_texture_path(a, a->map_pos.north_txt, a->north_texture);
	copy_texture_path(a, a->map_pos.south_txt, a->south_texture);
	copy_texture_path(a, a->map_pos.east_txt, a->east_texture);
	copy_texture_path(a, a->map_pos.west_txt, a->west_texture);
}
