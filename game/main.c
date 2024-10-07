/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:28:10 by csteudin          #+#    #+#             */
/*   Updated: 2024/10/07 07:06:06 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_exit(int exit_status)
{
	mlx_terminate(game()->mlx);
	mlx_delete_image(game()->mlx, game()->img);
	mlx_delete_image(game()->mlx, game()->tex->east_img);
	mlx_delete_image(game()->mlx, game()->tex->north_img);
	mlx_delete_image(game()->mlx, game()->tex->south_img);
	mlx_delete_image(game()->mlx, game()->tex->west_img);
	free_split(game()->map->map);
	exit(exit_status);
	return (exit_status);
}

int	main(int argc, char **argv)
{
	t_p		parsing;
	t_map	map;

	if (argc != 2)
		return (printf("Error: Needs just the map path to start\n"), 0);
	initialise_map(&map);
	if (main_parsing(argc, argv, &map, &parsing) != 0)
		return (ft_exit(EXIT_FAILURE));
	if (main_render(&map) != 0)
		return (ft_exit(EXIT_FAILURE));
	return (ft_exit(0));
}
