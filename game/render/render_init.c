/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:30:07 by csteudin          #+#    #+#             */
/*   Updated: 2024/10/04 13:30:32 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	initialise_map(t_map *map)
{
	ft_memset(map->map_name, '\0', sizeof(map->map_name));
	ft_memset(map->north_texture, '\0', sizeof(map->north_texture));
	ft_memset(map->south_texture, '\0', sizeof(map->south_texture));
	ft_memset(map->west_texture, '\0', sizeof(map->west_texture));
	ft_memset(map->east_texture, '\0', sizeof(map->east_texture));
	map->map = NULL;
	map->player_pos_x = 0;
	map->player_pos_y = 0;
	map->floor = 0;
	map->ceiling = 0;
	map->map_width = 0;
	map->map_height = 0;
}

int	initialise_mlx(void)
{
	game()->mlx = mlx_init(STD_WIDTH, STD_HEIGHT, "CUB-3D", false);
	if (game()->mlx == NULL)
		return (1);
	game()->img = mlx_new_image(game()->mlx, STD_WIDTH, STD_HEIGHT);
	if (game()->img == NULL)
		return (1);
	mlx_image_to_window(game()->mlx, game()->img, 0, 0);
	return (0);
}

void	initialise_map_size(void)
{
	int		x;
	int		y;
	char	**map;

	map = game()->map->map;
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (ft_strchr("NWSE", map[y][x]) != NULL)
				game()->player.direction = map[y][x];
			x++;
		}
		if (x > game()->map->map_width)
			game()->map->map_width = x;
		y++;
	}
	game()->map->map_height = y;
}

int	load_textures(void)
{
	int	scale_factor;
	int	texture_size;

	scale_factor = STD_WIDTH / STD_HEIGHT;
	texture_size = TILE * scale_factor * 4;
	game()->tex->north = mlx_load_png(game()->map->north_texture);
	game()->tex->south = mlx_load_png(game()->map->south_texture);
	game()->tex->east = mlx_load_png(game()->map->east_texture);
	game()->tex->west = mlx_load_png(game()->map->west_texture);
	// TODO: SPLIT HERE
	if (game()->tex->south == NULL || game()->tex->east == NULL
		|| game()->tex->west == NULL)
	{
		fprintf(stderr,
			"Fehler: Konnte eine oder mehrere Texturen nicht laden\n");
		return (1);
	}
	game()->tex->north_img = mlx_texture_to_image(game()->mlx,
			game()->tex->north);
	game()->tex->south_img = mlx_texture_to_image(game()->mlx,
			game()->tex->south);
	game()->tex->east_img = mlx_texture_to_image(game()->mlx,
			game()->tex->east);
	game()->tex->west_img = mlx_texture_to_image(game()->mlx,
			game()->tex->west);
	// TODO: SPLIT HERE
	if (game()->tex->north_img == NULL || game()->tex->south_img == NULL
		|| game()->tex->east_img == NULL || game()->tex->west_img == NULL)
	{
		fprintf(stderr,
			"Fehler: Konnte ein oder mehrere Bilder nicht konvertieren\n");
		return (1);
	}
	mlx_delete_texture(game()->tex->north);
	mlx_delete_texture(game()->tex->south);
	mlx_delete_texture(game()->tex->east);
	mlx_delete_texture(game()->tex->west);
	// TODO: SPLIT HERE
	if (mlx_resize_image(game()->tex->north_img, texture_size,
			texture_size) == false || mlx_resize_image(game()->tex->south_img,
			texture_size, texture_size) == false
		|| mlx_resize_image(game()->tex->east_img, texture_size,
			texture_size) == false || mlx_resize_image(game()->tex->west_img,
			texture_size, texture_size) == false)
	{
		fprintf(stderr,
			"Fehler: Konnte die Größe eines oder mehrerer Bilder nicht ändern\n");
		return (1);
	}
	return (0);
}

int	initialise_game(t_map *map)
{
	game()->mlx = NULL;
	game()->img = NULL;
	game()->map = map;
	game()->player.pos.x = (double)game()->map->player_pos_x * TILE + (TILE
			/ 2);
	game()->player.pos.y = (double)game()->map->player_pos_y * TILE + (TILE
			/ 2);
	game()->player.move_up = false;
	game()->player.move_down = false;
	game()->player.move_left = false;
	game()->player.move_right = false;
	game()->player.look_right = false;
	game()->player.look_left = false;
	game()->tex = malloc(sizeof(t_texture));
	game()->tex->north = NULL;
	game()->tex->south = NULL;
	game()->tex->west = NULL;
	game()->tex->east = NULL;
	game()->tex->north_img = NULL;
	game()->tex->south_img = NULL;
	game()->tex->west_img = NULL;
	game()->tex->east_img = NULL;
	initialise_map_size();
	game()->player.angle = get_start_angle(game()->player.direction);
	if (initialise_mlx() != 0 || load_textures() != 0)
		return (1);
	return (0);
}
