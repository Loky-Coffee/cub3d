/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:03:15 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/18 03:03:38 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING
#define PARSING

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
}t_p;


int		main_parsing(int argc, char **argv);
void	check_map_name(t_p *a);
int		open_map(t_p *a);
int		read_map(t_p *a);

#endif