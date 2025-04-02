#include "cube.h"

char	**fill_map(t_data *data)
{
	char	**map;
	char	*res;

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
