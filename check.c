/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:51:17 by yabuawad          #+#    #+#             */
/*   Updated: 2025/12/29 13:22:01 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_extension(char *filename)
{
	char	*arr;
	int		len;
	int		i;

	arr = "reb.";
	len = ft_strlen(filename);
	i = 0;
	while (len > 3 && i < 4)
	{
		if (filename[len - 1] != arr[i])
			return (0);
		else
		{
			i++;
			len--;
		}
	}
	return (1);
}

void	myfree(char **map, int n_lines)
{
	int	i;

	i = 0;
	while (i < n_lines && map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	mydestroy(t_game *game)
{
	if (game->texture.player)
		mlx_destroy_image(game->mlx_ptr, game->texture.player);
	if (game->texture.wall)
		mlx_destroy_image(game->mlx_ptr, game->texture.wall);
	if (game->texture.background)
		mlx_destroy_image(game->mlx_ptr, game->texture.background);
	if (game->texture.collec)
		mlx_destroy_image(game->mlx_ptr, game->texture.collec);
	if (game->texture.exit)
		mlx_destroy_image(game->mlx_ptr, game->texture.exit);
	return (0);
}

void	check_collectables(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'C')
				game->to_collect++;
			j++;
		}
		i++;
	}
}

int	destroy_all(t_game *game)
{
	if (!game)
		return (0);
	if (game->mlx_ptr)
		mydestroy(game);
	if (game->mlx_ptr && game->window)
		mlx_destroy_window(game->mlx_ptr, game->window);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	if (game->map)
		myfree(game->map, game->n_lines);
	exit(0);
	return (1);
}
