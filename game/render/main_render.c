/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:29:23 by csteudin          #+#    #+#             */
/*   Updated: 2024/10/04 13:29:45 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	render_movement();
	render_view(game);
}

int	main_render(t_map *map)
{
	if (initialise_game(map) != 0)
		return (1);
	main_hooks();
	mlx_loop(game()->mlx);
	return (0);
}
