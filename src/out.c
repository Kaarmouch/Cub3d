#include "cub3d.h"

void	free_texture(void *mlx, t_txt *texture)
{
	if (texture)
	{
		if (texture->img)
			mlx_destroy_image(mlx, texture->img);
		free(texture);
	}
}

void	free_info(t_info *info, void *mlx)
{
	free_texture(mlx, info->nw_txt);
	free_texture(mlx, info->sw_txt);
	free_texture(mlx, info->ew_txt);
	free_texture(mlx, info->ww_txt);
	if (info->flor_c)
		free_split(info->flor_c);
	if (info->celing_c)
		free_split(info->celing_c);
	free(info);
}

void	free_display(t_game *g)
{
	if (g->img)
		mlx_destroy_image(g->mlx, g->img);
	if (g->win && g->mlx)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_loop_end(g->mlx);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}

int	free_game(t_game *g)
{
	if (g->map)
	{
		if (g->map->info)
			free_info(g->map->info, g->mlx);
		free_display(g);
		if (g->map->fd != -1)
			close(g->map->fd);
		if (g->map->field)
			free_split(g->map->field);
		free(g->map);
	}
	if (g->p)
		free(g->p);
	return (1);
}

void	exit_with_error(t_game *game, const char *message)
{
	if (message)
		printf("Error: %s\n", message);
	free_game(game);
	exit(EXIT_FAILURE);
}
