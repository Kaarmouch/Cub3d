/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:51:28 by aglampor          #+#    #+#             */
/*   Updated: 2024/12/16 17:51:29 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	f_abs(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

double	min_step(double x, double y, double r)
{
	double	d_x;
	double	d_y;

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
	return (min((d_x / f_abs(cos(r))), (d_y / f_abs(sin(r)))));
}

unsigned int	rgb_to_hex(char **cs)
{
	int	r;
	int	g;
	int	b;

	r = atoi_color(cs[0]);
	g = atoi_color(cs[1]);
	b = atoi_color(cs[2]);
	return ((r << 16) | (g << 8) | b);
}

int	is_empty(char **map, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	if (map[grid_y][grid_x] == '1')
		return (0);
	if ((x - grid_x) == 0.0 && map[grid_y][grid_x - 1] == '1')
		return (0);
	if ((y - grid_y) == 0.0 && map[grid_y - 1][grid_x] == '1')
		return (0);
	return (1);
}

t_dd	*find_d(double r, double x, double y, char **field)
{
	double	step;
	t_dd	*info;

	info = malloc(sizeof(t_dd));
	info->d = 0.0;
	step = 0;
	while (is_empty(field, x, y))
	{
		step = min_step(x, y, r);
		info->d += step;
		x = x + cos(r) * step;
		y = y + sin(r) * step;
	}
	if (x - floor(x) < y - floor(y))
		info->col = f_abs(y - floor(y)) * 64;
	else
		info->col = f_abs(x - floor(x)) * 64;
	return (info);
}
