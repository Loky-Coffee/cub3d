/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_load_img_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 04:02:58 by csteudin          #+#    #+#             */
/*   Updated: 2024/10/07 06:28:09 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	load_img(void)
{
	game()->tex->north = mlx_load_png(game()->map->north_texture);
	game()->tex->south = mlx_load_png(game()->map->south_texture);
	game()->tex->east = mlx_load_png(game()->map->east_texture);
	game()->tex->west = mlx_load_png(game()->map->west_texture);
	if (game()->tex->south == NULL || game()->tex->east == NULL
		|| game()->tex->west == NULL)
	{
		printf("Error: couldnt load textures\n");
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
	if (game()->tex->north_img == NULL || game()->tex->south_img == NULL
		|| game()->tex->east_img == NULL || game()->tex->west_img == NULL)
	{
		printf("Error: couldnt convert textures to image\n");
		return (1);
	}
	return (0);
}

int	delete_textures(void)
{
	mlx_delete_texture(game()->tex->north);
	mlx_delete_texture(game()->tex->south);
	mlx_delete_texture(game()->tex->east);
	mlx_delete_texture(game()->tex->west);
	return (0);
}

int	load_textures(void)
{
	int	scale_factor;
	int	texture_size;

	scale_factor = STD_WIDTH / STD_HEIGHT;
	texture_size = TILE * scale_factor * 4;
	if (load_img() == 1)
		return (1);
	if (delete_textures() == 1)
		return (1);
	if (mlx_resize_image(game()->tex->north_img, texture_size,
			texture_size) == false || mlx_resize_image(game()->tex->south_img,
			texture_size, texture_size) == false
		|| mlx_resize_image(game()->tex->east_img, texture_size,
			texture_size) == false || mlx_resize_image(game()->tex->west_img,
			texture_size, texture_size) == false)
	{
		printf("Error: couldnt change image size\n");
		return (1);
	}
	return (0);
}
