/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:51:35 by yabuawad          #+#    #+#             */
/*   Updated: 2026/01/03 15:57:23 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_fill_img(t_game *game, int i, int j)
{
	mlx_put_image_to_window(game->mlx_ptr, game->window,
		game->texture.background, j * 64, i * 64);
	if (game->map[i][j] == '1')
		mlx_put_image_to_window(game->mlx_ptr, game->window, game->texture.wall,
			j * 64, i * 64);
	else if (game->map[i][j] == 'P')
		mlx_put_image_to_window(game->mlx_ptr, game->window,
			game->texture.player, j * 64, i * 64);
	else if (game->map[i][j] == 'C')
		mlx_put_image_to_window(game->mlx_ptr, game->window,
			game->texture.collec, j * 64, i * 64);
	else if (game->map[i][j] == 'E')
		mlx_put_image_to_window(game->mlx_ptr, game->window, game->texture.exit,
			j * 64, i * 64);
}

void	draw_game(t_game *game)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			my_fill_img(game, i, j);
			j++;
		}
		i++;
	}
	str = ft_itoa(game->n_movements);
	if (!str)
		return ;
	mlx_string_put(game->mlx_ptr, game->window, 100, 10, 0xFF00FF, str);
	mlx_string_put(game->mlx_ptr, game->window, 10, 10, 0xFF00FF, "MOVEMENTS:");
	free(str);
}

int	load_image(t_game *game)
{
	int	width;
	int	height;

	game->texture.background = mlx_xpm_file_to_image(game->mlx_ptr,"textures/background.xpm", &width, &height);
	game->texture.exit = mlx_xpm_file_to_image(game->mlx_ptr,"textures/exit.xpm", &width, &height);
	game->texture.wall = mlx_xpm_file_to_image(game->mlx_ptr,"textures/wall.xpm", &width, &height);
	game->texture.collec = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/collectable.xpm", &width, &height);
	game->texture.player = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/player.xpm", &width, &height);
	if (!game->texture.background || !game->texture.player
		|| !game->texture.collec || !game->texture.wall || !game->texture.exit)
	{
		mydestroy(game);
		return (0);
	}
	return (1);
}

int	update_pos(t_game *game, t_pos player, int old_x, int old_y)
{
	if (game->map[player.x][player.y] == '1')
		return (0);
	if (game->map[player.x][player.y] == 'C')
	{
		game->collected += 1;
	}
	if (game->map[player.x][player.y] == 'E')
	{
		if (game->collected != game->to_collect)
			write(1, "collect more items!\n", 20);
		else
		{
			game->n_movements++;
			write(1, "YOU WIN! 🎊🎉\n", 13);
			destroy_all(game);
		}
	}
	if (game->map[old_x][old_y] != 'E')
		game->map[old_x][old_y] = '0';
	if (game->map[player.x][player.y] != 'E')
		game->map[player.x][player.y] = 'P';
	return (1);
}

void	initialize_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return ;
	game->window = mlx_new_window(game->mlx_ptr, game->n_col * 64, game->n_lines
			* 64, "my game :3");
	if (!game->window)
		mydestroy(game);
	if (!load_image(game))
	{
		destroy_all(game);
		return ;
	}
	game->n_movements = 0;
	find_p(game->map, &game->player_pos, 'P');
	draw_game(game);
	mlx_hook(game->window, 2, 1L << 0, key_handle, game);
	mlx_hook(game->window, 17, 0, destroy_all, game);
	mlx_loop(game->mlx_ptr);
	free(game->mlx_ptr);
}
