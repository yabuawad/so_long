/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:52:34 by yabuawad          #+#    #+#             */
/*   Updated: 2026/01/03 15:54:29 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_p(char **map, t_pos *player, char figure)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == figure)
			{
				player->x = i;
				player->y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

char	**copy_map(char **map, int n_lines)
{
	int		i;
	char	**temp;
	int		j;

	temp = malloc((n_lines + 1) * sizeof(char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (map[i])
	{
		temp[i] = ft_strdup(map[i]);
		if (temp[i] == NULL)
		{
			j = -1;
			while (j++ < i)
			{
				free(temp[j]);
			}
			free(temp);
			return (NULL);
		}
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

void	flood_fill(char **temp_map, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->n_lines || y >= game->n_col)
		return ;
	if (temp_map[x][y] == '1' || temp_map[x][y] == '*' || temp_map[x][y] == '\0'
		|| temp_map[x][y] == '\n')
		return ;
	temp_map[x][y] = '*';
	flood_fill(temp_map, x + 1, y, game);
	flood_fill(temp_map, x - 1, y, game);
	flood_fill(temp_map, x, y + 1, game);
	flood_fill(temp_map, x, y - 1, game);
}

int	check_path(char **temp_map, int hight, int width)
{
	int	x;
	int	y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < hight)
		{
			if (temp_map[x][y] != '1' && temp_map[x][y] != '*')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int	validate_path(t_game *game)
{
	t_pos	player;
	int		n_col;
	char	**temp_map;

	temp_map = copy_map(game->map, game->n_lines);
	if (temp_map == NULL)
		return (0);
	n_col = check_rectangle(game->map, game->n_lines);
	find_p(game->map, &player, 'P');
	flood_fill(temp_map, player.x, player.y, game);
	if (!check_path(temp_map, n_col, game->n_lines))
	{
		myfree(temp_map, game->n_lines);
		return (0);
	}
	else
	{
		myfree(temp_map, game->n_lines);
		return (1);
	}
}
