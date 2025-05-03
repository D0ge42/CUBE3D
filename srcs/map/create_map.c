#include "cube.h"

static int skip_white_spaces(char *map);
static int ft_isspace(char c);

char	**fill_map(t_data *data)
{
	char	**map;
	char	*res;
  data->map->map_width = 0;

	map = ft_calloc(1, sizeof(char *));
	if (!map)
	{
		ft_putstr_fd("Malloc error\n", 2);
		return (NULL);
	}
	while (1)
	{
		res = get_next_line(data->map_ptr);
    if ((int)ft_strlen(res) > data->map->map_width)
      data->map->map_width = ft_strlen(res) - 1;
		if (!res)
			break ;
		data->map->map_height++;
		map = ft_strscat(map, res);
		if (!map)
		{
			free_strs(map);
			return (NULL);
		}
	}
	return (map);
}

void extract_map_only(t_data *data)
{
  int y = 0;
  int idx = 0;
  char **map = data->map->map;
  while(map[y] != NULL)
    y++;
  y-=1;
  while(map[y] && y >= 0)
  {
    idx = skip_white_spaces(map[y]);
    printf("%s",map[y]);
    if (map[y][idx] == '1')
      y--;
    else
      break;
  }
  data->map->map_start = y  + 1;
  data->map->map_height -= data->map->map_start;
}

int skip_white_spaces(char *map)
{
  int y = 0;
  while(ft_isspace(map[y]) == 1)
      y++;
  return y;
}

static int ft_isspace(char c)
{
  if (c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f' || c == 32)
    return 1;
  return 0;
}
