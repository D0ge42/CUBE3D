#include "cube.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	check_zeros_and_doors(t_data *data, char **map, int x, int y);
static void	check_player_existence(t_data *data);

void	is_map_closed(t_data *data)
{
	int		x;
	int		y;
	char	**map;
	int		max_width;

	y = data->map->map_start;
	map = data->map->map;
	max_width = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (max_width < (int)ft_strlen(map[y]))
				max_width = ft_strlen(map[y]) - 1;
			check_zeros_and_doors(data, map, x, y);
			x++;
		}
		y++;
	}
	data->map->map_width = max_width;
}

void	is_map_valid(t_data *data)
{
	char	**map;
	int		y;
	int		x;

	y = data->map->map_start;
	x = 0;
	map = data->map->map;
	while (map[y] && data->map->is_map_valid)
	{
		while (map[y][x])
		{
			if (check_and_set(data, map[y][x], x, y) == 0)
			{
				ft_putstr_fd(ERR_INVALID_MAP, 2);
				data->map->is_map_valid = 0;
				free_everything(data);
				exit(EXIT_FAILURE);
			}
			x++;
		}
		x ^= x;
		y++;
	}
	check_player_existence(data);
}

static void	check_player_existence(t_data *data)
{
	if (data->player->exists == 0 || data->player->exists > 1)
	{
		ft_putstr_fd(ERR_PLAYER_COUNT, 2);
		data->map->is_map_valid = 0;
		free_everything(data);
		exit(1);
	}
}

static void	check_zeros_and_doors(t_data *data, char **map, int x, int y)
{
	if ((map[y][x] == '0' || map[y][x] == 'P') && check_zero_surroundings(data,
			map, x, y) == 0)
	{
		ft_putstr_fd(ERR_MAP_NOT_CLOSED, 2);
		free_everything(data);
		exit(EXIT_FAILURE);
	}
}
