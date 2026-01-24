/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:14:09 by yabuawad          #+#    #+#             */
/*   Updated: 2025/12/29 13:14:12 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_wall_row(char **map, int n_lines, t_game *game)
{
	int	y;

	y = 0;
	while (map[0][y] != '\0')
	{
		if (map[0][y] == '1')
			y++;
		else if (map[0][y] == '\n')
			break ;
		else
			return (0);
	}
	if (!check_wall_col(map, y, n_lines, game))
		return (0);
	y = 0;
	while (map[n_lines - 1][y] != '\0')
	{
		if (map[n_lines - 1][y] == '1')
			y++;
		else if (map[n_lines - 1][y] == '\n')
			break ;
		else
			return (0);
	}
	return (1);
}
