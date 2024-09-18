/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:03:15 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/18 06:23:39 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct s_p
{
	char *map_name;
	char **map;
	char **argv;
	int argc;
	int map_fd;
	int floor_R;
	int floor_G;
	int floor_B;
	int ceiling_R;
	int ceiling_G;
	int ceiling_B;
}t_p;

// main_parsin
int		main_parsing(int argc, char **argv);

// load_map
void	check_map_name(t_p *a);
int		open_map(t_p *a);
int		read_map(t_p *a);
void	print_map(t_p *a);

// check_map_valid
int	check_map_Compass(t_p *a);
int check_map_colors(t_p *a);
int	check_path_to_texture(t_p *a);

#endif