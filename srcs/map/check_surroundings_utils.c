#include "cube.h"
#include <stdlib.h>


int	are_sorroundings_valid(t_data *data, char c)
{
	if (c && (c == 'P' || c == '0' || c == '1' || c == 'W' || c == 'N'
			|| c == 'S' || c == 'E'))
		return (1);
	else if (!c || is_space(c) == 1)
	{
		ft_putstr_fd(ERR_MAP_NOT_CLOSED, 2);
		free_everything(data);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd(ERR_INVALID_CHAR, 2);
		free_everything(data);
		exit(EXIT_FAILURE);
	}
}

int	is_coordinate_valid(char **tab, int x, int y)
{
	if (tab && y >= 0 && x >= 0 && x <= (int)ft_strlen(tab[y]) && tab[y]
		&& tab[y][x])
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == 0x20 || c == 0x0c || c == 0x0a || c == 0x0d || c == 0x09
		|| c == 0x0b)
		return (0x1);
	return (0x0);
}
