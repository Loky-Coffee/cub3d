/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:40:08 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/20 20:10:04 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	error_exit(t_p *a, char *error_msg, int error_code)
{
	printf(RED"%s\n"RESET, error_msg);
	if (a->map)
		free_split(a->map);
	exit(error_code);
}

static void	init_struct(t_p *a, int argc, char **argv)
{
	a->map = NULL;
	a->argc = argc;
	a->argv = argv;
	a->map_name = argv[1];
	a->map_fd = 0;
	a->floor.alpha = 0;
	a->floor.red = 0;
	a->floor.blue = 0;
	a->floor.green = 0;
	a->ceiling.alpha = 0;
	a->ceiling.red = 0;
	a->ceiling.blue = 0;
	a->ceiling.green = 0;
	ft_memset(a->north_texture, '\0', sizeof(a->north_texture));
	ft_memset(a->south_texture, '\0', sizeof(a->south_texture));
	ft_memset(a->west_texture, '\0', sizeof(a->west_texture));
	ft_memset(a->east_texture, '\0', sizeof(a->east_texture));
	a->map_pos.north_txt = -1;
	a->map_pos.south_txt = -1;
	a->map_pos.west_txt = -1;
	a->map_pos.east_txt = -1;
	a->map_pos.floor_color_pos = -1;
	a->map_pos.ceiling_color_pos = -1;
	a->map_pos.map_pos_start = -1;
	a->map_pos.map_pos_end = -1;
}

// void	print_map(t_p *a)
// {
// 	int	i;

// 	i = 0;
// 	while (a->map[i])
// 		printf("%s\n", a->map[i++]);
// 	printf("--------------------------------------------------------------\n");
// 	printf("north_texture PATH: %s\n", a->north_texture);
// 	printf("south_texture PATH: %s\n", a->south_texture);
// 	printf("west_texture PATH: %s\n", a->west_texture);
// 	printf("east_texture PATH: %s\n", a->east_texture);
// 	printf("--------------------------------------------------------------\n");
// 	printf("Floor red:%d, green:%d, blue:%d,  alpha:%d, Color:%08X \n", \
// 			a->floor.red, a->floor.green, a->floor.blue, a->floor.alpha, \
// 			a->floor.color);
// 	printf("--------------------------------------------------------------\n");
// 	printf("Ceiling red:%d, green:%d, blue:%d,  alpha:%d, Color:%08X \n", \
// 			a->ceiling.red, a->ceiling.green, a->ceiling.blue, \
// 			a->ceiling.alpha, a->ceiling.color);
// 	printf("--------------------------------------------------------------\n");
// 	printf("north_pos: %d\n", a->map_pos.north_txt);
// 	printf("south_txt: %d\n", a->map_pos.south_txt);
// 	printf("west_txt: %d\n", a->map_pos.west_txt);
// 	printf("east_txt: %d\n", a->map_pos.east_txt);
// 	printf("floor_color_pos: %d\n", a->map_pos.floor_color_pos);
// 	printf("ceiling_color_pos: %d\n", a->map_pos.ceiling_color_pos);
// 	printf("ceiling_color_pos: %d\n", a->map_pos.map_pos_start);
// 	printf("ceiling_color_pos: %d\n", a->map_pos.map_pos_end);
// }

int	main_parsing(int argc, char **argv, t_map *map, t_p *a) // TODO: add check if arguments are there so if argc is 1 then exit or if it are too many
{
	init_struct(a, argc, argv);
	check_map_name(a);
	open_map(a);
	read_map(a);
	if (check_map_identifier(a) != 0)
		return (free_split(a->map), 1);
	if (check_path_to_texture(a) != 0)
		return (free_split(a->map), 1);
	if (init_colors(a) != 0)
		return (free_split(a->map), 1);
	find_map_start(a);
	erase_oldmap(a);
	find_char_position(a);
	search_utils(a);
	// print_map(a);
	if (load_data_on_stack(a, map) != 0)
		return (free_split(a->map), 1);
	return (0);
}
	// if (!check_map_horizondal(&a))
	// 	return (free_split(a.map), 1);
	// if (!check_maps_vertikal(&a))
	// 	return (free_split(a.map), 1);
