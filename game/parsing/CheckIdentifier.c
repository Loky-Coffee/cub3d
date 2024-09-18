/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckIdentifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 04:16:13 by aalatzas          #+#    #+#             */
/*   Updated: 2024/09/18 15:41:13 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_map_identifier(t_p *a)
{
	size_t i;

	i = 0;
	while (i < 6)
	{
		if (i == 0 && !(ft_strncmp(a->map[i], "NO ", 3) == 0))
			return (printf("ERROR:\n north Identifier must be NO"), 1);
		if (i == 1 && !(ft_strncmp(a->map[i], "SO ", 3) == 0))
			return (printf("ERROR:\n south Identifier must be SO"), 1);
		if (i == 2 && !(ft_strncmp(a->map[i], "WE ", 3) == 0))
			return (printf("ERROR:\n west Identifier must be WE"), 1);
		if (i == 3 && !(ft_strncmp(a->map[i], "EA ", 3) == 0))
			return (printf("ERROR:\n east Identifier must be EA"), 1);
		if (i == 4 && !(ft_strncmp(a->map[i], "F ", 2) == 0))
			return (printf("ERROR:\n Floor color Identifier must be F"), 1);
		if (i == 5 && !(ft_strncmp(a->map[i], "C ", 2) == 0))
			return (printf("ERROR:\n Ceiling color Identifier must be C"), 1);
		i++;
	}
	return (0);
}
