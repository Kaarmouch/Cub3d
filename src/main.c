#include "cub3d.h"

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

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || !is_argok(argv[1]))
		return (write(1, "ERROR\n", 6));
	init_game(&game, argv[1]);
	load_cube(&game);
	draw(&game, game.map, game.p);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
