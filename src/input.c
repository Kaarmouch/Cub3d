/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:53:21 by aglampor          #+#    #+#             */
/*   Updated: 2024/12/16 17:53:23 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mv(int key, t_game *g)
{
	double	new_x;
	double	new_y;
	double	ofst;
	double	a;

	a = g->p->vect_p;
	ofst = 0.1;
	if (key == KEY_D)
		a += PI;
	else if (key == KEY_R)
		a += PI / 2;
	else if (key == KEY_L)
		a += -PI / 2;
	new_x = g->p->x + ofst * cos(a);
	new_y = g->p->y + ofst * sin(a);
	if (!is_wall(g->map->field, new_x + ofst * cos(a), new_y + ofst * sin(a)))
	{
		g->p->x = new_x;
		g->p->y = new_y;
	}
}

void	ft_rotate(int key, t_game *g)
{
	if (key == KEY_A)
	{
		g->p->vect_p -= 0.1;
		g->p->vect_c -= 0.1;
	}
	else if (key == KEY_E)
	{
		g->p->vect_p += 0.1;
		g->p->vect_c += 0.1;
	}
}

int	key_press(int key, t_game *g)
{
	printf("aqui %i\n", key);
	if (key == KEY_ESC)
		exit_with_error(g, "BYE");
	if (key == 122 || key == 113
		|| key == 115 || key == 100)
		ft_mv(key, g);
	if (key == KEY_A || key == KEY_E)
		ft_rotate(key, g);
	mlx_clear_window(g->mlx, g->win);
	draw(g, g->map, g->p);
	return (0);
}
