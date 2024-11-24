#include "cub3d.h"


#include <stdio.h>

void print_texture(t_txt *txt, char *label)
{
    printf("Texture %s:\n", label);
    if (txt)
    {
        printf("  img: %p\n", txt->img);
        printf("  data: %p\n", txt->data);
        printf("  bpp: %d\n", txt->bpp);
        printf("  size_line: %d\n", txt->size_line);
        printf("  endian: %d\n", txt->endian);
    }
    else
    {
        printf("  %s texture is NULL\n", label);
    }
}

void print_info(t_info *info)
{
    printf("Info Structure:\n");
    if (info)
    {
        print_texture(info->nw_txt, "North Wall");
        print_texture(info->sw_txt, "South Wall");
        print_texture(info->ew_txt, "East Wall");
        print_texture(info->ww_txt, "West Wall");
        printf("  Floor Colors: %s,%s,%s\n", info->flor_c[0], info->flor_c[1], info->flor_c[2]);
        printf("  Ceiling Colors: %s,%s,%s\n", info->celing_c[0], info->celing_c[1], info->celing_c[2]);
    }
    else
    {
        printf("  Info structure is NULL\n");
    }
}

void print_map(t_map *map)
{
    printf("Map Structure:\n");
    if (map)
    {
        printf("  File Descriptor: %d\n", map->fd);
        printf("  Height (H): %d\n", map->H);
        printf("  Width (W): %d\n", map->W);

        if (map->field)
        {
            printf("  Terrain:\n");
            for (int i = 0; map->field[i] != NULL; i++)
            {
                printf("[%i] %s\n",i, map->field[i]);
            }
        }
        else
        {
            printf("  Terrain is NULL\n");
        }

        print_info(map->info);
    }
    else
    {
        printf("  Map structure is NULL\n");
    }
}

void print_player(t_player *player)
{
    printf("Player Structure:\n");
    if (player)
    {
        printf("  Position X: %lf\n", player->x);
        printf("  Position Y: %lf\n", player->y);
	printf("  Player Vector (radians): %.2f\n", player->vect_p);
        printf("  Cosine of Player Vector: %.2f\n", cos(player->vect_p));
        printf("  Sine of Player Vector: %.2f\n", sin(player->vect_p));
        printf("  Camera Vector (radians): %.2f\n", player->vect_c);
    }
    else
    {
        printf("  Player structure is NULL\n");
    }
}

void print_game(t_game *game)
{
    printf("Game Structure:\n");
    if (game)
    {
        printf("  MLX Pointer: %p\n", game->mlx);
        printf("  Window Pointer: %p\n", game->win);
        printf("  Image Pointer: %p\n", game->img);
        printf("  Data Pointer: %p\n", game->data);
        printf("  Bits per Pixel: %d\n", game->bits_pp);
        printf("  Size Line: %d\n", game->s_line);
        printf("  Endian: %d\n", game->endian);

        print_map(game->map);
        print_player(game->p);
    }
    else
    {
        printf("  Game structure is NULL\n");
    }
}

int	is_argok(char *path)
{
	int	flag;

	flag = find_c(path, '.');
	if (flag == -1)
		return (0);
	if (!(ft_cmp(&path[flag], ".cub")))
		return (0);
	return (1);
}

double	min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

double	f_abs(double a)
{
	if(a < 0)
		return (-a);
	return (a);
}

int	is_wall(char **map, double x, double y)
{
	int grid_x;
	int grid_y;

	grid_x = (int)x;
	grid_y = (int)y;

	if (grid_x < 0 || grid_y < 0 || map[grid_y] == NULL || map[grid_y][grid_x] == '\0')
		return (1); // Considère hors limites comme un mur
	return (map[grid_y][grid_x] == '1');
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || !is_argok(argv[1]))
		return (write(1,"ERROR\n", 6));
	init_game(&game, argv[1]);
	load_cube(&game);
	print_game(&game);
	draw(&game, game.map, game.p);
	mlx_hook(game.win, 17, 0, (int (*)())free_game, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
