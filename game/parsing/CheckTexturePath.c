/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckTexturePath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:48:47 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/18 06:23:27 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_path_to_texture(t_p *a)
{
	size_t i;
	size_t y;
	char line[4096];

	i = 0;
	while (i < 4)
	{
		y = 0;
		while (a->map[i][y] != ' ' && a->map[i][y] != '\0')
			y++;
		while (a->map[i][y] == ' ')
			y++;
		strncpy(line, &a->map[i][y], sizeof(line) - 1);
		line[sizeof(line) - 1] = '\0';
		a->map_fd = open(line, O_RDONLY);
		if (a->map_fd == -1)
			return (perror(line), 1);
		close(a->map_fd);
		i++;
	}
	return (0);
}