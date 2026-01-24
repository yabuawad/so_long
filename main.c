/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:51:25 by yabuawad          #+#    #+#             */
/*   Updated: 2026/01/03 15:28:20 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_map(char **map, char *argv)
{
	int		x;
	int		fd;
	char	*line;
	int		len;

	x = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while ((line))
	{
		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
			line[--len] = '\0';
		map[x] = line;
		line = get_next_line(fd);
		x++;
	}
	close(fd);
	map[x] = NULL;
}

int	count_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	count = 0;
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while ((line))
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	return (count);
}

int	mycheck(t_game *game, char *argv)
{
	if (!check_map_extension(argv))
	{
		write(2, "Error! Wrong extention\n", 24);
		myfree(game->map, game->n_lines);
		return (0);
	}
	if (!check_wall_row(game->map, game->n_lines, game))
	{
		write(2, "error\n", 7);
		myfree(game->map, game->n_lines);
		return (0);
	}
	if (!validate_path(game))
	{
		write(2, "error invalid path\n", 20);
		myfree(game->map, game->n_lines);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (0);
	ft_memset(&game, 0, sizeof(game));
	game.n_lines = count_lines(argv[1]);
	if (game.n_lines == 0)
		return (0);
	game.map = malloc((game.n_lines + 1) * sizeof(char *));
	if (!game.map)
		return (0);
	fill_map(game.map, argv[1]);
	if (!game.n_lines)
	{
		myfree(game.map, game.n_lines);
		return (0);
	}
	if (!mycheck(&game, argv[1]))
		return (0);
	game.to_collect = 0;
	game.collected = 0;
	check_collectables(&game);
	initialize_game(&game);
	myfree(game.map, game.n_lines);
}

// map file is basically just the initial source of a map
//,then its saved in the 2d array.
// any further change is just change in memory.source map remains unchanged
//-L tells the compiler WHERE to look & -l tells it what to use
// ( -L<folder> &&-l<name of lib without lib & .a>)
//  -I is for including the header path
// X window system is what makes graphical interface possible in linux...
//  mlx library is based on X window system
// struct.obj == passes struct value
// struct->obj == passes struct through pointer
