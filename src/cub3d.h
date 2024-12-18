/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:51:11 by aglampor          #+#    #+#             */
/*   Updated: 2024/12/18 15:50:57 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../minilibx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

# define BUFFER_SIZE 42
# define PI 3.141592
# define KEY_ESC 65307
# define KEY_D 115
# define KEY_U 122
# define KEY_L 113
# define KEY_R 100
# define KEY_A 65361
# define KEY_E 65363
# define WIDTH 750
# define HT 750

typedef struct s_coordo
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_draw_data
{
	double	d;
	int		col;
}	t_dd;

typedef struct s_texture
{
	void		*img;
	int			*data;
	int			bpp;
	int			s_line;
	int			endian;
}	t_txt;

typedef struct s_info
{
	t_txt	*nw_txt;
	t_txt	*sw_txt;
	t_txt	*ew_txt;
	t_txt	*ww_txt;
	char	**flor_c;
	char	**celing_c;
}	t_info;

typedef struct s_map
{
	int				fd;
	char			**field;
	int				h;
	int				w;
	struct s_info	*info;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	vect_p;
	double	vect_c;
}	t_player;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*data;
	int				bits_pp;
	int				s_line;
	int				endian;
	struct s_map	*map;
	struct s_player	*p;
}	t_game;

int				is_wall(char **map, double x, double y);
double			min(double a, double b);
double			f_abs(double a);
int				is_argok(char *path);
/*	gnl	*/

char			*get_next_info(int fd);
char			*ft_strdup(char *src);

/*	clean_init	*/
void			init_texture(t_txt *texture);
int				init_info(t_info *info);
int				init_map(t_map *map, char *path);
void			init_player(t_player *player);
void			init_game(t_game *game, char *path);

/*	utils	*/
int				find_c(char *str, char c);
int				ft_cmp(char *o, char *t);
int				ft_len(char *s);
char			*wrd_dup(char *str, int start, int finish);
char			**supstr_dup(char **src, int nb_l);

/*	input	*/
int				key_press(int keycode, t_game *g);
void			ft_rotate(int key, t_game *g);
void			ft_mv(int key, t_game *g);

/*	b_utils	*/
int				flood(char **map, int x, int y, int H);
int				is_terrain(char *terr);
void			free_split(char	**split);
int				is_white(char *fantom);

/*	draw	*/
void			draw(t_game *g, t_map *m, t_player *p);
void			draw_column(t_game *g, int x, t_dd *i, t_txt *txt);
t_txt			*giv_txt(t_txt *a, t_txt *b, int hit);
t_txt			*get_txt(t_info *ifs, double r, double d, t_pos *p);

/*	d_utils	*/
int				is_empty(char **map, double x, double y);
double			min_step(double x, double y, double r);
unsigned int	rgb_to_hex(char **cs);
t_dd			*find_d(double r, double x, double y, char **field);

/*	colors	*/
int				ft_strt_angle(char c);
int				atoi_color(char *str);
int				is_color(char *c);
int				get_colors(char **dst, char *colors);

/*	build_game	*/
int				add_wall_txt(t_game *g, t_info *info, char *path, int *i);
int				build_map(t_game *game, t_map *map);
int				build_terrain(t_map *map, char *line, int idx);
int				info_player(char **m, t_player *p);

/*	load	*/
void			load_img(t_game *g);
void			load_mlx(t_game *g);
void			load_cube(t_game *g);
int				load_texture(t_txt *t, char *path, void *mlx);

/*	out	*/
void			free_display(t_game *g);
void			free_texture(void *mlx, t_txt *texture);
void			free_info(t_info *info, void *mlx);
int				free_game(t_game *game);
void			exit_with_error(t_game *game, const char *message);

/* SO Phreauguane // Rmidou pour les textures <trois	*/
#endif 
