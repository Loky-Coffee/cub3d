/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:03:15 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/19 07:00:47 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#ifndef MAX_PATH_LENGTH
#define MAX_PATH_LENGTH 4096
#endif

typedef union s_color
{
	u_int32_t		color;
	struct
	{
		unsigned char red;
		unsigned char green;
		unsigned char blue;
		unsigned char alpha;
	};
} t_color;

typedef struct s_p
{
	int		argc;
	char	**argv;
	int		map_fd;
	char	*map_name;
	char	**map;
	char	north_texture[MAX_PATH_LENGTH];
	char	south_texture[MAX_PATH_LENGTH];
	char	west_texture[MAX_PATH_LENGTH];
	char	east_texture[MAX_PATH_LENGTH];
	t_color	floor;
	t_color	ceiling;
}t_p;

// main_parsin
int		main_parsing(int argc, char **argv);

// load_map
void	check_map_name(t_p *a);
int		open_map(t_p *a);
int		read_map(t_p *a);
void	print_map(t_p *a);

// check_map_valid
int		check_map_identifier(t_p *a);
int		check_map_colors(t_p *a);
int		check_path_to_texture(t_p *a);
int		load_data_on_stack(t_p *a);

#endif