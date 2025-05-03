#include "cube.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>

void are_all_info_present(t_data *data);

void	is_map_closed(t_data *data)
{
	int		x;
	int		y;
	char	**map;

	y = data->map->map_start;
	map = data->map->map;
	while (map[y])
	{
		x = 0;

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

void are_all_info_present(t_data *data)
{
  if (data->map->we_txt_path == NULL ||
    data->map->so_txt_path == NULL ||
    data->map->no_txt_path == NULL ||
    data->map->ea_txt_path == NULL ||
    data->map->ceiling_info == NULL ||
    data->map->floor_info == NULL)
    {
    free_everything(data);
    ft_putstr_fd("Error: Some info are missing\n", 2);
    exit(1);
  }
}


