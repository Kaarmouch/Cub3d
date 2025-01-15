/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:53:50 by aglampor          #+#    #+#             */
/*   Updated: 2024/12/16 17:53:51 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_img(t_game *g)
{
	char	*adr;

	g->img = mlx_new_image(g->mlx, WIDTH, HT);
	if (!(g->img))
		exit_with_error(g, "Failled to allocate memory for mlx_img");
	adr = mlx_get_data_addr(g->img, &g->bits_pp, &g->s_line, &g->endian);
	g->data = (int *)adr;
}

void	load_mlx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		exit_with_error(g, "Failled init the mlx");
	g->win = mlx_new_window(g->mlx, WIDTH, HT, "1CUB3DEN22");
	if (!g->win)
		exit_with_error(g, "Failled init the new window");
}

void	load_cube(t_game *g)
{
	char	**cpy;
	int		out;

	load_mlx(g);
	load_img(g);
	if (!(build_map(g, g->map)))
		exit_with_error(g, "Prompt error : I dont want none of that sh*t");
	if (!(info_player(g->map->field, g->p)))
		exit_with_error(g, "Prompt error : info player");
	cpy = supstr_dup(g->map->field, g->map->h);
	out = flood(cpy, g->p->x, g->p->y, g->map->h);
	free_split(cpy);
	if (out)
		exit_with_error(g, "Prompt error : Map cant flood");
}

int	load_texture(t_txt *t, char *path, void *mlx)
{
	int	w;
	int	h;

	if (t->img)
		return (0);
	t->img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!t->img)
		return (0);
	t->data = (int *)mlx_get_data_addr(t->img, &t->bpp, &t->s_line, &t->endian);
	return (1);
}
