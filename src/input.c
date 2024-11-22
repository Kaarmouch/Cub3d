#include "cub3d.h"

void	ft_mv(int key, t_game *g)
{
	double new_x;
	double new_y;

	new_x = g->p->x;
	new_y = g->p->y;
	if (key == KEY_U)  // Move forward
	{
		new_x += 0.1 * cos(g->p->vect_p);
		new_y += 0.1 * sin(g->p->vect_p);
	}
	else if (key == KEY_D)  // Move backward
	{
		new_x -= 0.1 * cos(g->p->vect_p);
		new_y -= 0.1 * sin(g->p->vect_p);
	}
	else if (key == KEY_R)  // Strafe right
	{
		new_x += 0.1 * cos(g->p->vect_p + PI/2);
		new_y += 0.1 * sin(g->p->vect_p + PI/2);
	}
	else if (key == KEY_L)  // Strafe left
	{
		new_x += 0.1 * cos(g->p->vect_p - PI/2);
		new_y += 0.1 * sin(g->p->vect_p - PI/2);
	}
	if (!is_wall(g->map->field, new_x, new_y))
	{
		g->p->x = new_x;
		g->p->y = new_y;
	}
}

void	ft_rotate(int key, t_game *g)
{
	if (key == KEY_A)  // Rotate player left
	{
		g->p->vect_p -= 0.1;
		g->p->vect_c -= 0.1;
	}
	else if (key == KEY_E)  // Rotate player right
	{
		g->p->vect_p += 0.1;
		g->p->vect_c += 0.1;
	}
}

int     key_press(int key, t_game *g)
{
	printf("aqui %i\n",key);
        if (key == KEY_ESC) // escap
                exit_with_error(g ,"BYE");
        if (key == 122  || key == 113
			|| key == 115 || key == 100)
                ft_mv(key, g);
	if (key == KEY_A || key == KEY_E)
		ft_rotate(key, g);
        mlx_clear_window(g->mlx, g->win);
        draw(g, g->map, g->p);
        return (0);
}

