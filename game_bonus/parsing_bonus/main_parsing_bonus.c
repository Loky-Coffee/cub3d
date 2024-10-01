/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:40:08 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/24 19:47:23 by csteudin         ###   ########.fr       */
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

static void	init_t_pos_struct(t_p *a)
{
	a->map_pos.north_txt = -1;
	a->map_pos.south_txt = -1;
	a->map_pos.west_txt = -1;
	a->map_pos.east_txt = -1;
	a->map_pos.floor_color_pos = -1;
	a->map_pos.ceiling_color_pos = -1;
	a->map_pos.map_pos_start = -1;
	a->map_pos.map_pos_end = -1;
}

static void	init_t_color_struct(t_p *a)
{
	a->floor.alpha = 0;
	a->floor.red = 0;
	a->floor.blue = 0;
	a->floor.green = 0;
	a->ceiling.alpha = 0;
	a->ceiling.red = 0;
	a->ceiling.blue = 0;
	a->ceiling.green = 0;
}

static void	init_t_p_struct(t_p *a, int argc, char **argv)
{
	a->argc = argc;
	a->argv = argv;
	a->map_fd = 0;
	a->map_name = argv[1];
	a->map = NULL;
	a->buff_map = NULL;
	a->map_not_valid = false;
	a->start_find = false;
	ft_memset(a->north_texture, '\0', sizeof(a->north_texture));
	ft_memset(a->south_texture, '\0', sizeof(a->south_texture));
	ft_memset(a->west_texture, '\0', sizeof(a->west_texture));
	ft_memset(a->east_texture, '\0', sizeof(a->east_texture));
}

int	main_parsing(int argc, char **argv, t_map *map, t_p *a)
{
	if (argc != 2)
		return (1);
	init_t_p_struct(a, argc, argv);
	init_t_pos_struct(a);
	init_t_color_struct(a);
	load_map(a);
	check_map_identifier(a);
	load_texture_path(a);
	load_colors(a);
	find_map_start(a);
	erase_oldmap(a);
	find_char_position(a);
	search_utils(a);
	if (load_data_on_stack(a, map) != 0)
		return (free_split(a->map), 1);
	return (0);
}
