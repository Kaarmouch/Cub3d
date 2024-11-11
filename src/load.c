#include "cub3d.h"

void    load_img(t_game *g)
{
        char	*adr;

        g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
        if (!(g->img))
                exit_with_error(g, "Failled to allocate memory for mlx_img");
        adr = mlx_get_data_addr(g->img, &g->bits_pp, &g->s_line, &g->endian);
        g->data = (int *)adr;
}

void    load_mlx(t_game *g)
{
        g->mlx = mlx_init();
        if (!g->mlx)
                exit_with_error(g, "Failled init the mlx");
        g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "1CUB3DEN22");
        if (!g->win)
                exit_with_error(g, "Failled init the new window");
}

void	load_cube(t_game *g)
{	
	char	**cpy;
	int	out;

	load_mlx(g);
	load_img(g);
	if (!(build_map(g, g->map)))
		exit_with_error(g, "Prompt error : I dont want none of that sh*t");
	if (!(info_player(g->map->field, g->p)))
		exit_with_error(g, "Prompt error : info player");
	cpy = supstr_dup(g->map->field, g->map->H);
	out = flood(cpy, g->p->x, g->p->y, g->map->H);
	free_split(cpy);
	if (out)
		exit_with_error(g, "Prompt error : Map cant flood");
}

int     load_texture(t_txt *t, char *path, void *mlx)
{
	int	w;
	int	h;

        t->img = mlx_xpm_file_to_image(mlx, path, &w, &h);
        if (!t->img)
                return (0);
        t->data = (int *)mlx_get_data_addr(t->img, &t->bpp, &t->size_line, &t->endian);
        return (1);
}
