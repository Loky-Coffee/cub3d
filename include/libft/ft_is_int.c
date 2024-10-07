/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:41:43 by aalatzas          #+#    #+#             */
/*   Updated: 2024/10/07 07:48:23 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_only_one_minus(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-' || str[i] == '+')
		{
			x++;
			if (x == 2)
				ft_error("Error1\n", 1);
		}
		i++;
	}
}

static void	ist_not_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((!ft_isdigit(str[i])) && (str[i] != '-') && (str[i] != '+'))
			ft_error("Error2\n", 1);
		i++;
	}
	check_only_one_minus(str);
}

/// @brief Checks if the string is a valid int
/// @param str The string to check
/// @return int 1 if the string is a valid int, 0 otherwise
int	ft_is_int(char *str)
{
	ist_not_char(str);
	if (str[0] == '-')
	{
		if (ft_strlen(str) > 11)
			ft_error("Error3\n", 1);
		if (ft_strlen(str) == 11)
		{
			if (ft_strncmp(str, "-2147483648", 11) > 0)
				ft_error("Error4\n", 1);
		}
	}
	else
	{
		if (ft_strlen(str) > 10)
			ft_error("Error5\n", 1);
		if (ft_strlen(str) == 10)
		{
			if (ft_strncmp(str, "2147483647", 10) > 0)
				ft_error("Error6\n", 1);
		}
	}
	return (1);
}
