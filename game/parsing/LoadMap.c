/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadMap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:38:03 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/21 02:08:18 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


static void	open_map(t_p *a)
{
	a->map_fd = open(a->map_name, O_RDONLY);
	if (a->map_fd == -1)
		error_exit(a, "ERROR: Cannot open map file", 1);
}

static void	read_map(t_p *a)
{
	char	*line;
	char	*buff;
	char	*temp;

	line = NULL;
	buff = NULL;
	temp = NULL;
	while (true)
	{
		line = get_next_line(a->map_fd);
		if (line == NULL)
			break ;
		temp = ft_strjoin(buff, line);
		if (temp == NULL)
			error_exit(a, "ERROR: ft_strjoin LoadMap: line.66", 1);
		free(buff);
		buff = temp;
		free(line);
	}
	close(a->map_fd);
	a->map = ft_split(buff, '\n');
	free(buff);
}

void	load_map(t_p *a)
{
	const char	*p;

	p = ft_strrchr(a->map_name, '.');
	if (p == NULL)
		error_exit(a, "ERROR: Only '.cub' files are accepted.", 1);
	if (ft_strncmp(p, ".cub", ft_strlen(".cub") + 1) != 0)
		error_exit(a, "ERROR: Only '.cub' files are accepted.", 1);
	open_map(a);
	read_map(a);
}