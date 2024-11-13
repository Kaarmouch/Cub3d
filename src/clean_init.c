#include "cub3d.h"

void init_texture(t_txt *texture)
{
	memset(texture, 0, sizeof(texture));
}

int	init_info(t_info *info) 
{
	info->nw_txt = malloc(sizeof(t_txt));
	info->sw_txt = malloc(sizeof(t_txt));
	info->ew_txt = malloc(sizeof(t_txt));
	info->ww_txt = malloc(sizeof(t_txt));
	if (!info->nw_txt || !info->sw_txt || !info->ew_txt || !info->ww_txt)
		return (0);
	init_texture(info->nw_txt);
	init_texture(info->ew_txt);
	init_texture(info->ww_txt);
	init_texture(info->sw_txt);
	info->flor_c = malloc(sizeof(char *) * 4);
	info->celing_c = malloc(sizeof(char *) * 4);
	if (!info->celing_c || !info->flor_c)
		return (0);
	return (1);
}

int	init_map(t_map *map, char *path)
{
	map->fd = open(path, O_RDONLY);
	map->H = 0;
	map->W = 0;
	map->field = NULL;
	map->info = malloc(sizeof(t_info));
	if (!map->info)
		return (0);
	if (!init_info(map->info))
		return (0);
	return (1);
}

void	init_player(t_player *player)
{
	player->x = -1.0;
	player->y = -1.0;
	player->vect_p = -1.0;
	player->vect_c = -1.0;
}

void	init_game(t_game *game, char *path)
{
	memset(game, 0, sizeof(game));
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		exit_with_error(game, "Failed to allocate memory for map");
	if (!init_map(game->map, path))
		exit_with_error(game, "Failed to init map");
	game->p = malloc(sizeof(t_player));
	if (!game->p)
		exit_with_error(game, "Failed to allocate memory for player");
	init_player(game->p);
}
