#include "cub3d.h"
double	min_step(double x, double y, double r)
{
	double	d_x;
	double	d_y;
	double	out;

	if (cos(r) > 0)
		d_x = 1 + (int)x - x;
	else
	{
		d_x = x - (int)x;
		if (!d_x)
			d_x = 1;
	}
	if (sin(r) > 0)
		d_y = 1 + ((int)y - y);
	else
	{
		d_y = y - (int)y;
		if (!d_y)
			d_y = 1;
	}
	if (!cos(r))
		return (d_y);
	else if (!sin(r))
		return (d_x);
	out = min((d_x/f_abs(cos(r))) , (d_y/f_abs(sin(r))));
	return (out);
}

int	is_empty(char **map, double x, double y)
{
	int grid_x = (int)x;
	int grid_y = (int)y;

	if (map[grid_y][grid_x] == '1')
		return (0);
	if ((x - grid_x) == 0.0 && map[grid_y][grid_x - 1] == '1')
		return (0);
	if ((y - grid_y) == 0.0 && map[grid_y - 1][grid_x] == '1')
		return (0);
	return (1);
}


double	find_d(double r, double x, double y, char **field)
{
	double	dist;
	double	step;
	int	i = 0;

	dist = 0.0;
	step = 0;
	while (is_empty(field, x , y))
	{
		step = min_step(x, y, r);
		dist += step;
		x = x + cos(r) * step;
		y = y + sin(r) * step;
	}
	return(dist);
}

unsigned int rgb_to_hex(char **cs)
{
	int	r;
	int	g;
	int	b;

	r = atoi_color(cs[0]);
	g = atoi_color(cs[1]);
	b = atoi_color(cs[2]);

	return ((r << 16) | (g << 8) | b);
}

void	draw_column(t_game *g, int x, double d, t_txt *txt)
{
	int				wall_h;
	int				startY;
	int				endY;
	int				y;
	unsigned int	color;

	wall_h = (int)(HEIGHT / d);
	startY = (HEIGHT - wall_h) / 2;
	endY = startY + wall_h;
	if (startY < 0)
		startY = 0;
	if (endY >= HEIGHT)
		endY = HEIGHT - 1;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < startY) // Ciel
			color = rgb_to_hex(g->map->info->celing_c);
		else if (y >= startY && y <= endY) // Mur avec texture
			color = txt->data[((y - startY) * 64 / wall_h) * 64 + (x % 64)];
		else if (y > endY) // Sol
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
		offset = f_abs(p->vect_c - ray);
		d = (find_d(ray, p->x, p->y, m->field)) * cos(offset);
		ray += step;
		draw_column(g, x, d, g->map->info->ew_txt);
		x+=1;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}

