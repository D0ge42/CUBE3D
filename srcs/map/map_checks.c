#include "cube.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
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
			if (map[y][x] == '0' && check_zero_surroundings(data,map, x, y) == 0)
			{
        ft_putstr_fd(ERR_MAP_NOT_CLOSED,2);
        free_everything(data);
				exit(EXIT_FAILURE);
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
        ft_putstr_fd(ERR_INVALID_MAP, 2);
				data->map->is_map_valid = 0;
        free_everything(data);
				exit(EXIT_FAILURE);
			}
			x++;
		}
		x = 0;
		y++;
	}
	if (data->player->exists == 0 || data->player->exists > 1)
	{
    ft_putstr_fd(ERR_PLAYER_COUNT, 2);
		data->map->is_map_valid = 0;
    free_everything(data);
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
      printf("%p\n",data->map->we_txt_path);
      printf("%p\n",data->map->ea_txt_path);
      printf("%p\n",data->map->no_txt_path);
      printf("%p\n",data->map->so_txt_path);
      printf("%p\n",data->map->ceiling_info);
      printf("%p\n",data->map->floor_info);
    free_everything(data);
    ft_putstr_fd("Error: Some info are missing\n", 2);
    exit(1);
  }
}


