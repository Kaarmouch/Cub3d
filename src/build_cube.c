/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:50:34 by aglampor          #+#    #+#             */
/*   Updated: 2024/12/16 17:50:37 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_wall_txt(t_game *g, t_info *info, char *path, int *i)
{
	char	*tmp;
	int		ok;

	tmp = wrd_dup(path, (find_c(path, ' ') + 1), ft_len(path));
	ok = 0;
	if (!find_c(path, 'N') && !find_c(&path[1], 'O'))
		ok = load_texture(info->nw_txt, tmp, g->mlx);
	if (!find_c(path, 'S') && !find_c(&path[1], 'O'))
		ok = load_texture(info->sw_txt, tmp, g->mlx);
	if (!find_c(path, 'W') && !find_c(&path[1], 'E'))
		ok = load_texture(info->ww_txt, tmp, g->mlx);
	if (!find_c(path, 'E') && !find_c(&path[1], 'A'))
		ok = load_texture(info->ew_txt, tmp, g->mlx);
	if (!find_c(path, 'F'))
		ok = get_colors(info->flor_c, tmp);
	if (!find_c(path, 'C'))
		ok = get_colors(info->celing_c, tmp);
	free(tmp);
	*i += ok;
	return (ok);
}

int	info_player(char **m, t_player *p)
{
	int	l;
	int	c;

	l = 0;
	c = 0;
	while (m[l])
	{
		if (m[l][c] == 'E' || m[l][c] == 'S' || m[l][c] == 'W'
				|| m[l][c] == 'N')
			break ;
		c++;
		if (!m[l][c])
		{
			c = 0;
			l++;
		}
	}
	if (!m[l])
		return (0);
	p->x = c + 0.5;
	p->y = l + 0.5;
	p->vect_p = (ft_strt_angle(m[l][c]) * PI / 180);
	m[l][c] = '0';
	p->vect_c = p->vect_p;
	return (1);
}

int	build_terrain(t_map *map, char *line, int idx)
{
	char	**tmp;
	int		i;

	i = 0;
	map->h = idx + 1;
	tmp = malloc(sizeof(char *) * (idx + 2));
	if (!tmp)
		return (0);
	while (map->field && map->field[i])
	{
		tmp[i] = ft_strdup(map->field[i]);
		i++;
	}
	tmp[idx] = ft_strdup(line);
	tmp[idx + 1] = NULL ;
	if (map->field)
		free_split(map->field);
	map->field = tmp;
	if (!is_terrain(map->field[idx]))
		return (0);
	if (map->w <= ft_len(map->field[idx]))
		map->w = ft_len(map->field[idx]);
	return (1);
}

int	build_map(t_game *g, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_info(map->fd);
		if (!line)
			break ;
		if (i < 6 && line[0])
		{
			if (!add_wall_txt(g, map->info, line, &i))
				return (free(line), 0);
		}
		else if (line[0])
		{
			if (!build_terrain(map, line, (i - 6)))
				return (free(line), 0);
			i++;
		}
		free(line);
	}
	if (i < 6)
		return (0);
	return (1);
}
