/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:03:15 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/21 02:11:38 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# ifndef MAX_PATH_LENGTH
#  define MAX_PATH_LENGTH 4096
# endif

#include "cub3d.h"
# define RED "\033[31m"
# define GREEN "\033[92m"
# define YELLOW "\033[93m"
# define BLUE "\033[94m"
# define MAGENTA "\033[95m"
# define CYAN "\033[96m"
# define RESET "\033[0m"

typedef union s_color
{
	u_int32_t		color;
	struct
	{
		unsigned char	alpha;
		unsigned char	red;
		unsigned char	green;
		unsigned char	blue;
	};
}	t_color;

typedef struct s_pos
{
	int		north_txt;
	int		south_txt;
	int		west_txt;
	int		east_txt;
	int		floor_color_pos;
	int		ceiling_color_pos;
	int		map_pos_start;
	int		map_pos_end;
	int		player_x;
	int		player_y;
}	t_pos;

typedef struct s_p
{
	int		argc;
	char	**argv;
	int		map_fd;
	char	*map_name;
	char	**map;
	char	**buff_map;
	bool	map_not_valid;
	bool	start_find;
	char	north_texture[MAX_PATH_LENGTH];
	char	south_texture[MAX_PATH_LENGTH];
	char	west_texture[MAX_PATH_LENGTH];
	char	east_texture[MAX_PATH_LENGTH];
	t_color	floor;
	t_color	ceiling;
	t_pos	map_pos;

}	t_p;

// main_parsin
int		main_parsing(int argc, char **argv, t_map *map, t_p *a);
int		error_exit(t_p *a, char *error_msg, int error_code);

// load_map
void	load_map(t_p *a);

//checkcolorsRGB.c
void	load_colors(t_p *a);

//CheckIdentifier.c
void	check_map_identifier(t_p *a);

//load_texture_path.c
void		load_texture_path(t_p *a);

// check_map.c
void	find_map_start(t_p *a);
void	find_char_position(t_p *a);
void	search_utils(t_p *a);

//load_data_on_stack.c
void	erase_oldmap(t_p *a);
int		load_data_on_stack(t_p *src, t_map *dest);


#endif