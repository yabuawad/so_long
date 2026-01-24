/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:52:28 by yabuawad          #+#    #+#             */
/*   Updated: 2026/01/03 15:33:40 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_dup(char **map, char figure)
{
	int	x;
	int	y;
	int	flag;

	x = 0;
	y = 0;
	flag = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y] && map[x][y] != '\n')
		{
			if (map[x][y] == figure)
				flag++;
			y++;
		}
		x++;
	}
	if (flag == 1)
		return (1);
	else
		return (flag);
}

int	check_valid(char **map, int n_lines)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (x < n_lines)
	{
		y = 0;
		while (map[x][y] != '\n' && map[x][y] != '\0')
		{
			if (map[x][y] == 'E' || map[x][y] == 'P' || map[x][y] == 'C'
				|| map[x][y] == '1' || map[x][y] == '0')
				y++;
			else
				return (0);
		}
		x++;
	}
	return (1);
}

int	check_rectangle(char **map, int n_lines)
{
	int	y;
	int	first_row;

	y = 0;
	first_row = 0;
	if (!check_valid(map, n_lines))
		return (0);
	if (check_dup(map, 'E') != 1 || check_dup(map, 'P') != 1)
		return (0);
	if (check_dup(map, 'C') < 1)
		return (0);
	while (map[0][first_row] != '\0' && map[0][first_row] != '\n')
		first_row++;
	while (n_lines - 1 >= 0)
	{
		while (map[n_lines - 1][y] && map[n_lines - 1][y] != '\n')
			y++;
		if (y != first_row)
			return (0);
		y = 0;
		n_lines--;
	}
	return (first_row);
}

int	check_first_row(int x, int n_lines, char **map)
{
	while (x < n_lines && map[x][0] != '\0')
	{
		if (map[x][0] == '1')
			x++;
		else if (map[x][0] == '\n')
			x++;
		else
			return (0);
	}
	return (1);
}

int	check_wall_col(char **map, int n_col, int n_lines, t_game *game)
{
	int	x;

	x = 0;
	game->n_col = check_rectangle(map, n_lines);
	if (!game->n_col)
		return (0);
	if (!check_first_row(x, n_lines, map))
		return (0);
	while (x < n_lines && map[x][n_col - 1] != '\0')
	{
		if (map[x][n_col - 1] == '1')
			x++;
		else if (map[x][n_col - 1] == '\n')
			x++;
		else
			return (0);
	}
	return (1);
}
