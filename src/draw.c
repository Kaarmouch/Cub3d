#include "cub3d.h"
t_txt	*get_txt(t_info *ifs, double r, double d, double posX, double posY)
{
    double impactX;
    double impactY;
    int is_vertical_hit;

    is_vertical_hit = 0;
    impactX = posX + d * cos(r);
    impactY = posY + d * sin(r);
    if (f_abs(impactX - floor(impactX)) < f_abs(impactY - floor(impactY)))
        is_vertical_hit = 1;  // Impact sur un bord vertical (Est ou Ouest)
    if (is_vertical_hit)
    {
        if (cos(r) > 0)
            return ifs->ew_txt;  // Bord Est
        else
            return ifs->ww_txt;  // Bord Ouest
    }
    else
    {
        if (sin(r) > 0)
            return ifs->nw_txt;  // Bord Nord
        else
            return ifs->sw_txt;  // Bord Sud
    }
}

void	draw_column(t_game *g, int x, double d, int col, t_txt *txt)
{
	int				texY;
	int				startY;
	int				endY;
	int				y;
	unsigned int	color;

	startY = (HEIGHT - (int)(HEIGHT / d)) / 2;
	endY = startY + (int)(HEIGHT / d);
	if (startY < 0)
		startY = 0;
	if (endY >= HEIGHT)
		endY = HEIGHT - 1;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < startY)
			color = rgb_to_hex(g->map->info->celing_c);
		else if (y >= startY && y <= endY)
		{
			texY = fmax(0, fmin(63, ((y - (HEIGHT - (int)(HEIGHT / d)) / 2) * 64) / (int)(HEIGHT /d)));
			color = txt->data[texY * 64 + (col % 64)];
		}
		else if (y > endY)
			color = rgb_to_hex(g->map->info->flor_c);
		((unsigned int *)g->data)[y * WIDTH + x] = color;
		y++;
	}
}


void	draw(t_game *g, t_map *m, t_player *p)
{
	int	x;
	double	ray;
	double	offset;
	double	d;
	double	step;

	d = 0.0;
	ray = p->vect_c - (PI / 6);
	step = (PI/3) / WIDTH;
	x = 0;
	while (x < WIDTH)
	{
		int colonne;
		offset = f_abs(p->vect_c - ray);
		d = (find_d(ray, p->x, p->y, m->field, &colonne)) * cos(offset);
		draw_column(g, x, d, colonne, get_txt(g->map->info ,ray, d, p->x, p->y));
		ray += step;
		x+=1;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}
