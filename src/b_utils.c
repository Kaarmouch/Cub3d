/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:50:47 by aglampor          #+#    #+#             */
/*   Updated: 2024/12/16 17:50:48 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	is_terrain(char *terr)
{
	int	i;

	i = 0;
	while (terr[i])
	{
		if (terr[i] == 'N' || terr[i] == 'W'
			|| terr[i] == 'E' || terr[i] == 'S')
			;
		else if (terr[i] != '1' && terr[i] != '0'
			&& terr[i] != ' ' && terr[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	is_wall(char **map, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_x < 0 || grid_y < 0 || map[grid_y] == NULL
		|| map[grid_y][grid_x] == '\0')
		return (1);
	return (map[grid_y][grid_x] == '1');
}

int	is_white(char *ftm)
{
	int	i;

	i = 0;
	while (ftm[i])
	{
		if (ftm[i] != ' ' || ftm[i] != '\t')
			return (0);
		i += 1;
	}
	return (1);
}

int	flood(char **map, int x, int y, int H)
{
	if (x < 0 || y >= H || y < 0
		|| x >= ft_len(map[y])
		|| map[y][x] == '\0'
		|| map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1')
		return (0);
	map[y][x] = '1';
	return (flood(map, x + 1, y, H)
		|| flood(map, x, y + 1, H)
		|| flood(map, x, y - 1, H)
		|| flood(map, x - 1, y, H));
}
