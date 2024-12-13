#include "cub3d.h"

t_txt	*get_txt(t_info *ifs, double r, double d, t_pos *p)
{
	double	ipct_x;
	double	ipct_y;
	int		vertic_hit;

	vertic_hit = 0;
	ipct_x = p->x + d * cos(r);
	ipct_y = p->y + d * sin(r);
	if (f_abs(ipct_x - round(ipct_x)) < f_abs(ipct_y - round(ipct_y)))
		vertic_hit = 1;
	if (vertic_hit)
	{
		if (cos(r) > 0)
			return (ifs->ww_txt);
		else
			return (ifs->ew_txt);
	}
	else
	{
		if (sin(r) > 0)
			return (ifs->sw_txt);
		else
			return (ifs->nw_txt);
	}
}

void	draw_column(t_game *g, int x, t_dd *i, t_txt *txt)
{
	int				t_y;
	int				s_y;
	int				e_y;
	int				y;
	unsigned int	color;

	s_y = fmax(0, (HEIGHT - (int)(HEIGHT / i->d)) / 2);
	e_y = fmin(HEIGHT - 1, strt_y + (int)(HEIGHT / i->d));
	y = 0;
	while (y < HEIGHT)
	{
		if (y < strt_y)
			color = rgb_to_hex(g->map->info->celing_c);
		else if (y >= s_y && y <= e_y)
		{
			t_y = fmax(0, fmin(63, ((y - s_y) * 64) / (int)(HEIGHT / i->d)));
			color = txt->data[t_y * 64 + (i->col % 64)];
		}
		else if (y > end_y)
			color = rgb_to_hex(g->map->info->flor_c);
		((unsigned int *)g->data)[y * WIDTH + x] = color;
		y++;
	}
}

void	draw(t_game *g, t_map *m, t_player *p)
{
	t_dd	*i;
	t_pos	*pos;
	int		x;
	double	ray;
	double	offset;

	pos = malloc(sizeof(t_pos));
	if (!pos)
		return ;
	pos->x = p->x;
	pos->y = p->y;
	ray = p->vect_c - (PI / 6);
	x = 0;
	while (x < WIDTH)
	{
		offset = f_abs(p->vect_c - ray);
		i = find_d(ray, p->x, p->y, m->field);
		i->d *= cos(offset);
		draw_column(g, x, i, get_txt(g->map->info, ray, i->d, pos));
		free(i);
		ray += ((PI / 3) / WIDTH);
		x += 1;
	}
	free(pos);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}
