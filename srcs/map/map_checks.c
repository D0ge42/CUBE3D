#include "cube.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>

static int	extract_and_skip_map_infos(t_data *data, int x, int y);
static void extract_path(t_data *data, char *path, char *which);
static void extract_color(t_data *data, char *map_line);

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
		if (extract_and_skip_map_infos(data, x, y) == 1)
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
		if (extract_and_skip_map_infos(data, x, y) == 1)
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

static int	extract_and_skip_map_infos(t_data *data, int x, int y)
{
  char **map = data->map->map;
	if (ft_strncmp(map[y], "NO ", 3) == 0)
  {
    if (!data->map->no_txt_path)
      extract_path(data, map[y],"NO ");
		return (1);
  }
	if (ft_strncmp(map[y], "SO ", 3) == 0)
  {
    if (!data->map->so_txt_path)
      extract_path(data,map[y],"SO ");
    return (1);
  }
	if (ft_strncmp(map[y], "WE ", 3) == 0)
  {
    if (!data->map->we_txt_path)
      extract_path(data, map[y], "WE ");
		return (1);
  }
	if (ft_strncmp(map[y], "EA ", 3) == 0)
  {
    if (!data->map->ea_txt_path)
      extract_path(data, map[y], "EA ");
    return (1);
  }
	if (map[y][x] == 'F' || map[y][x] == 'C')
  {
    extract_color(data,map[y]);
		return (1);
  }
	return (0);
}


static void extract_path(t_data *data, char *map_line, char *which)
{
  int idx = 0;
  while(map_line[idx] && map_line[idx] != '.')
    idx++;
  if (!data->map->ea_txt_path && ft_strncmp(which,"EA ",3) == 0)
  {
      data->map->ea_txt_path = ft_calloc(1,ft_strlen(map_line + 1));
      memmove(data->map->ea_txt_path,&map_line[idx],ft_strlen(map_line) - idx);
  }
  if (!data->map->we_txt_path && ft_strncmp(which,"WE ",3) == 0)
  {
      data->map->we_txt_path = ft_calloc(1,ft_strlen(map_line + 1));
      memmove(data->map->we_txt_path,&map_line[idx],ft_strlen(map_line) - idx);
  }
  if (!data->map->so_txt_path && ft_strncmp(which,"SO ",3) == 0)
  {
      data->map->so_txt_path = ft_calloc(1,ft_strlen(map_line + 1));
      memmove(data->map->so_txt_path,&map_line[idx],ft_strlen(map_line) - idx);
  }
  if (!data->map->no_txt_path && ft_strncmp(which,"NO ",3) == 0)
  {
      data->map->no_txt_path = ft_calloc(1,ft_strlen(map_line + 1));
      memmove(data->map->no_txt_path,&map_line[idx],ft_strlen(map_line) - idx);
  }
}

static void extract_color(t_data *data, char *map_line)
{
  int idx = 0;
  while(map_line[idx] && !ft_isdigit(map_line[idx]))
    idx++;
  if (!data->map->ceiling_info)
  {
    data->map->ceiling_info = ft_calloc(1,ft_strlen(map_line) + 1);
    memmove(data->map->ceiling_info,&map_line[idx],ft_strlen(map_line) - idx);
  }
  else if (!data->map->floor_info)
  {
    data->map->floor_info = ft_calloc(1,ft_strlen(map_line) + 1);
    memmove(data->map->floor_info,&map_line[idx],ft_strlen(map_line) - idx);
  }
}
