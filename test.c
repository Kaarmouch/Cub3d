#include <stdio.h>
int	main()
{
	float	idx;
	int	i;

	i = 0;
	idx = 0;
	while (i < 100)
	{
		printf("float %f, soit %i en int\n",idx, (int)idx);
		if ((int)(idx + 0.5) == (int)(idx + 1))
		{
			printf("bordure !\n");
			idx += ((float)((int)idx) + 1) - idx;
		}
		else
			idx+=0.1;
		i++;
	}
	return (1);
}
