#include "cube.h"
#include <stdio.h>

static int	skip_map_infos(char **map, int x, int y);

void	is_map_closed(t_data *data)
{
	int		x;
	int		y;
	char	**map;

	y = 0;
	map = data->map->map;
	while (map[y])
	{
		x = 0;
		if (skip_map_infos(map, x, y) == 1)
		{
			y++;
			continue ;
		}
		while (map[y][x])
		{
			if (map[y][x] == '0' && check_zero_surroundings(map, x, y) == 0)
			{
				printf("Error: map not closed\n");
				exit(1);
			}
			x++;
		}
		y++;
	}
}

static int	skip_map_infos(char **map, int x, int y)
{
	if (ft_strncmp(map[y], "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(map[y], "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(map[y], "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(map[y], "EA ", 3) == 0)
		return (1);
	if (map[y][x] == 'F' || map[y][x] == 'C')
		return (1);
	return (0);
}

void	is_map_valid(t_data *data)
{
	char	**map;
	int		y;
	int		x;

	y = 0;
	x = 0;
	map = data->map->map;
	while (map[y] && data->map->is_map_valid)
	{
		if (skip_map_infos(map, x, y) == 1)
		{
			y++;
			continue ;
		}
		while (map[y][x])
		{
			if (check_and_set(data, map[y][x], x, y) == 0)
			{
				printf("Error: map not valid\n");
				data->map->is_map_valid = 0;
				exit(1);
			}
			x++;
		}
		x = 0;
		y++;
	}
	if (data->player->exists == 0 || data->player->exists > 1)
	{
		printf("Error: player count invalid\n");
		data->map->is_map_valid = 0;
		exit(1);
	}
}
