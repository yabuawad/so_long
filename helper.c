/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:06:01 by yabuawad          #+#    #+#             */
/*   Updated: 2025/12/30 17:53:59 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_memset(void *strng, int cha, size_t n)
{
	size_t			i;
	unsigned char	*s;

	s = strng;
	i = 0;
	while (i < n)
	{
		s[i] = cha;
		i++;
	}
	return (strng);
}

int	get_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		++len;
	while (nbr != 0)
	{
		++len;
		nbr = nbr / 10;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*result;
	int		len;

	if (nbr == 0)
		return (ft_strdup("0"));
	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	len = get_len(nbr);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	result[len] = '\0';
	while (nbr != 0)
	{
		--len;
		result[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (result);
}

void	keys(t_game *game, int keycode, t_pos *new_pos)
{
	if (keycode == 119)
	{
		new_pos->x--;
		if (game->map[new_pos->x][new_pos->y] != '1')
			game->n_movements++;
	}
	else if (keycode == 115)
	{
		new_pos->x++;
		if (game->map[new_pos->x][new_pos->y] != '1')
			game->n_movements++;
	}
	else if (keycode == 97)
	{
		new_pos->y--;
		if (game->map[new_pos->x][new_pos->y] != '1')
			game->n_movements++;
	}
	else if (keycode == 100)
	{
		new_pos->y++;
		if (game->map[new_pos->x][new_pos->y] != '1')
			game->n_movements++;
	}
}

int	key_handle(int keycode, void *param)
{
	t_game	*game;
	t_pos	new_pos;
	int		old_x;
	int		old_y;

	game = (t_game *)param;
	new_pos = game->player_pos;
	old_x = game->player_pos.x;
	old_y = game->player_pos.y;
	if (keycode == 65307)
		destroy_all(game);
	else
		keys(game, keycode, &new_pos);
	if (update_pos(game, new_pos, old_x, old_y))
		game->player_pos = new_pos;
	draw_game(game);
	return (0);
}
