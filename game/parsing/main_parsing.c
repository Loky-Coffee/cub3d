/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:40:08 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/18 03:39:27 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_struct(t_p *a, int argc, char **argv)
{
	a->map = NULL;
	a->argc = argc;
	a->argv = argv;
	a->map_name = argv[1];
}

int	main_parsing(int argc, char **argv)
{
	t_p	a;

	init_struct(&a, argc, argv);
	check_map_name(&a);
	open_map(&a);
	read_map(&a);
	return (0);
}
