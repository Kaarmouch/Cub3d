#include "cub3d.h"

int	ft_len(char *s)
{
	int	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

char	**supstr_dup(char **src, int nb_l)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (nb_l + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < nb_l)
	{
		new[i] = ft_strdup(src[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*wrd_dup(char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

int	ft_cmp(char *o, char *t)
{
	int	i;

	i = 0;
	while (o[i])
	{
		if (o[i] != t[i])
			return (0);
		i++;
	}
	if(t[i])
		return (0);
	return (1);
}


int	find_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
