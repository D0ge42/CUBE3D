#include "cube.h"
#include "libft.h"
#include <string.h>

static int skip_white_spaces(char *map);
static int ft_isspace(char c);
static void extract_map_infos(t_data *data, int x, int y);
static void extract_path(t_data *data, char *path, char *which);
static void extract_color(t_data *data, char *map_line, char which);
static int is_info(char *curr);

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
  while(map[y + 1] != NULL)
  {
    idx = skip_white_spaces(map[y]);
    if (is_info(&map[y][idx]) == 1)
      y++;
    else
      break;
  }
  data->map->map_start = y ;
  data->map->map_height -= data->map->map_start;
}


static int is_info(char *curr)
{
	if (ft_strncmp(curr, "NO ", 3) == 0 || ft_strncmp(curr,"N ", 2) == 0)
    return 1;
	if (ft_strncmp(curr, "SO ", 3) == 0 || ft_strncmp(curr,"S ", 2) == 0)
    return 1;
	if (ft_strncmp(curr, "WE ", 3) == 0 || ft_strncmp(curr,"W ", 2) == 0)
    return 1;
	if (ft_strncmp(curr, "EA ", 3) == 0 || ft_strncmp(curr, "E ",2) == 0)
    return 1;
  if (ft_strncmp(curr,"F ",2) == 0)
    return 1;
  if (ft_strncmp(curr,"C ",2) == 0)
    return 1;
  if (strcmp(curr,"") == 0)
    return 1;
  return 0;
}

void get_map_infos(t_data *data)
{
  int start = data->map->map_start;
  char **map = data->map->map;
  while(start >= 0 && map[start])
  {
    int idx = skip_white_spaces(map[start]);
    extract_map_infos(data,idx,start);
    start--;
  }
  are_all_info_present(data);
}

int skip_white_spaces(char *map)
{
  int y = 0;
  while(map[y] && ft_isspace(map[y]) == 1)
      y++;
  return y;
}

static int ft_isspace(char c)
{
  if (c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f' || c == 32)
    return 1;
  return 0;
}

void extract_map_infos(t_data *data, int x, int y)
{
  char **map = data->map->map;
	if (ft_strncmp(&map[y][x], "NO ", 3) == 0 || ft_strncmp(&map[y][x],"N ", 2) == 0)
  {
    if (!data->map->no_txt_path)
      extract_path(data, map[y],"NO ");
  }
	if (ft_strncmp(&map[y][x], "SO ", 3) == 0 || ft_strncmp(&map[y][x],"S ", 2) == 0)
  {
    if (!data->map->so_txt_path)
      extract_path(data,map[y],"SO ");
  }
	if (ft_strncmp(&map[y][x], "WE ", 3) == 0 || ft_strncmp(&map[y][x],"W ", 2) == 0)
  {
    if (!data->map->we_txt_path)
      extract_path(data, map[y], "WE ");
  }
	if (ft_strncmp(&map[y][x], "EA ", 3) == 0 || ft_strncmp(&map[y][x], "E ",2) == 0)
  {
    if (!data->map->ea_txt_path)
      extract_path(data, map[y], "EA ");
  }
  if (ft_strncmp(&map[y][x],"F ", 2) == 0)
    extract_color(data,map[y],'F');
	if (ft_strncmp(&map[y][x],"C ",2) == 0)
    extract_color(data,map[y],'C');
}


void extract_path(t_data *data, char *map_line, char *which)
{
  int idx = 0;
  int end = 0;
  while(map_line[idx] && ft_isspace(map_line[idx]))
    idx++;
  while(map_line && map_line[idx] && map_line[idx] >= 'A' && map_line[idx] <= 'Z')
    idx++;
  while(map_line[idx] && ft_isspace(map_line[idx]))
    idx++;
  end = idx;
  while(map_line[end] && map_line[end] != '\n')
    end++;
  if (!data->map->ea_txt_path && ft_strncmp(which,"EA ",3) == 0)
  {
      data->map->ea_txt_path = ft_calloc(1,ft_strlen(map_line + 1));
      memmove(data->map->ea_txt_path,&map_line[idx],end - idx);
  }
  if (!data->map->we_txt_path && ft_strncmp(which,"WE ",3) == 0)
  {
      data->map->we_txt_path = ft_calloc(1,ft_strlen(map_line + 1));
      memmove(data->map->we_txt_path,&map_line[idx],end - idx);
  }
  if (!data->map->so_txt_path && ft_strncmp(which,"SO ",3) == 0)
  {
      data->map->so_txt_path = ft_calloc(1,ft_strlen(map_line + 1));
      memmove(data->map->so_txt_path,&map_line[idx],end - idx);
  }
  if (!data->map->no_txt_path && ft_strncmp(which,"NO ",3) == 0)
  {
      data->map->no_txt_path = ft_calloc(1,ft_strlen(map_line + 1));
      memmove(data->map->no_txt_path,&map_line[idx],end - idx);
  }
}

static void extract_color(t_data *data, char *map_line, char which)
{
  int idx = 0;
  while(map_line[idx] && ft_isspace(map_line[idx]))
    idx++;
  while(map_line[idx] && (map_line[idx] == 'F' || map_line[idx] == 'C'))
    idx++;
  while(map_line[idx] && ft_isspace(map_line[idx]))
    idx++;
  if (!data->map->ceiling_info && which == 'C')
  {
    data->map->ceiling_info = ft_calloc(1,ft_strlen(map_line) + 1);
    memmove(data->map->ceiling_info,&map_line[idx],ft_strlen(map_line) - idx);
  }
  else if (!data->map->floor_info && which == 'F')
  {
    data->map->floor_info = ft_calloc(1,ft_strlen(map_line) + 1);
    memmove(data->map->floor_info,&map_line[idx],ft_strlen(map_line) - idx);
  }
}

