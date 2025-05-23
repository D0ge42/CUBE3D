#include "cube.h"

char	**ft_strscat(char **map, char *str)
{
	int		i;
	int		strs_num;
	char	**new_array;

	i = 0;
	strs_num = ft_strslen(map);
	new_array = ft_calloc(strs_num + 2, sizeof(char *));
	if (!new_array)
	{
		ft_putstr_fd("Malloc error\n", 2);
		return (NULL);
	}
	while (map && map[i])
	{
		new_array[i] = map[i];
		i++;
	}
	new_array[i] = str;
	free(map);
	return (new_array);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int	ft_strslen(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		i++;
	return (i);
}

void	print_strs(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

void free_everything(t_data *data)
{
  free(data->map->ea_txt_path);
  free(data->map->no_txt_path);
  free(data->map->so_txt_path);
  free(data->map->we_txt_path);
  free(data->map->ceiling_info);
  free(data->map->floor_info);
  free_strs(data->map->map);
}
