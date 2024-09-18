/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:40:08 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/18 08:01:19 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_struct(t_p *a, int argc, char **argv)
{
	a->map = NULL;
	a->argc = argc;
	a->argv = argv;
	a->map_name = argv[1];
	a->map_fd = 0;
	a->floor_rgb[0] = 0;
	a->floor_rgb[1] = 0;
	a->floor_rgb[2] = 0;
	a->ceiling_rgb[0] = 0;
	a->ceiling_rgb[1] = 0;
	a->ceiling_rgb[2] = 0;
}

int	main_parsing(int argc, char **argv)
{
	t_p	a;

	init_struct(&a, argc, argv);

	// check map name and load
	check_map_name(&a);
	open_map(&a);
	read_map(&a);

	//Printmap Debug Funktion!
	print_map(&a);

	//check map_valid or not!
	if(check_map_Compass(&a) != 0)
		return(free_split(a.map), 1);
	if (check_path_to_texture(&a) != 0)
		return(free_split(a.map), 1);
	if (check_map_colors(&a) != 0)
		return(free_split(a.map), 1);
	// if (!check_map_horizondal(&a))
	// 	return(free_split(a.map), 1);
	// if (!check_maps_vertikal(&a))
	// 	return(free_split(a.map), 1);
	return (0);
}
