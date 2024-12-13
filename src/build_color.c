#include "cub3d.h"

int	ft_strt_angle(char c)
{
	if (c == 'N')
		return (270);
	if (c == 'S')
		return (90);
	if (c == 'W')
		return (180);
	if (c == 'E')
		return (0);
	return (-1);
}

int	atoi_color(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		nbr = nbr * 10 + (str[i] - '0');
		i += 1;
	}
	return (nbr);
}

int	is_color(char *c)
{
	int	i;
	int	nb;
	int	flag;

	flag = 0;
	i = 0;
	if (!c || !c[i])
		return (0);
	while (c[i])
	{
		if (c[i] == ',')
		{
			if (i == 0 || flag > 2)
				return (0);
			flag += 1;
		}
		else if (c[i] > '9' || c[i] < '0')
			return (0);
		i += 1;
	}
	if (flag != 2)
		return (0);
	return (1);
}

int	get_colors(char **dst, char *colors)
{
	int	strt;
	int	end;
	int	i;

	strt = 0;
	i = 0;
	end = 0;
	if (!dst || !is_color(colors))
		return (0);
	while (i < 3)
	{
		if (i < 2)
			end += find_c(&colors[strt], ',');
		else
			end = ft_len(colors);
		dst[i] = wrd_dup(colors, strt, end);
		strt = end + 1;
		end += 1;
		i++;
	}
	dst[i] = NULL;
	return (1);
}
