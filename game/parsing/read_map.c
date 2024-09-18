/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:38:03 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/18 03:04:37 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void check_map_name(t_p *a)
{
	const char	*p;

	p = ft_strrchr(a->map_name, '.');
	if (p == NULL)
	{
		printf("Error: Only '.cub' files are accepted.");
		exit (EXIT_FAILURE);
	}
	if (ft_strncmp(p, ".cub", ft_strlen(".cub") + 1) != 0)
	{
		printf("Error: Only '.cub' files are accepted.");
		exit (EXIT_FAILURE);
	}
}

int open_map(t_p *a)
{
	int fd;

	if ((fd = open(a->map_name, O_RDONLY)) == -1)
	{
		perror("Error: Cannot open map file\n");
		exit(1);
	}
	return (0);
}

int read_map(t_p *a)
{

}