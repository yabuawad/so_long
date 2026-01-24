/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:53:08 by yabuawad          #+#    #+#             */
/*   Updated: 2025/12/29 13:27:09 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct positions
{
	int			x;
	int			y;
}				t_pos;

typedef struct texture
{
	void		*player;
	void		*wall;
	void		*background;
	void		*collec;
	void		*exit;
}				t_texture;

typedef struct game
{
	t_texture	texture;
	t_pos		player_pos;
	t_pos		exit_pos;
	void		*mlx_ptr;
	void		*window;
	char		**map;
	int			n_lines;
	int			n_col;
	int			to_collect;
	int			collected;
	int			n_movements;
}				t_game;
char			*get_next_line(int fd);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char *s1, char *s2);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_strdup(const char *s);
int				ft_strlen(const char *str);

int				check_wall_row(char **map, int n_lines, t_game *game);
int				check_wall_col(char **map, int n_col, int n_lines,
					t_game *game);
int				check_rectangle(char **map, int n_lines);
int				validate_path(t_game *game);
void			myfree(char **map, int n_lines);
int				check_map_extension(char *filename);
void			find_p(char **map, t_pos *player, char figure);
int				mydestroy(t_game *game);
void			initialize_game(t_game *game);
int				load_image(t_game *game);
void			draw_game(t_game *game);
int				check_path(char **temp_map, int hight, int width);
void			my_fill_img(t_game *game, int i, int j);
void			check_collectables(t_game *game);
char			*ft_itoa(int nbr);
void			*ft_memset(void *strng, int cha, size_t n);
int				destroy_all(t_game *game);
int				key_handle(int keycode, void *param);
int				update_pos(t_game *game, t_pos player, int old_x, int old_y);
int				check_wall_col(char **map, int n_col, int n_lines,
					t_game *game);
#endif
