#include "cube.h"

char **ft_strscat(char **map, char *str)
{
	int i;
	int strs_num;
	char **new_array;

	i = 0;
	strs_num = ft_strslen(map);
	new_array = ft_calloc(strs_num + 2, sizeof(char *));
	if (!new_array)
	{
		ft_putstr_fd("Malloc error\n",2);
		return NULL;
	}
	while(map && map[i])
	{
		new_array[i] = map[i];
		i++;
	}
	new_array[i] = str;
	free(map);
	return new_array;
}

void free_strs(char **strs)
{
	int i;
	
	i = 0;
	while(strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int ft_strslen(char **strs)
{
	int i = 0;
	while(strs && strs[i])
		i++;
	return i;
}

void print_map(char **map)
{
	int i = 0;
	while(map && map[i])
	{
		printf("%s",map[i]);
		i++;
	}
}

void detect_player(t_data *data,char c, int x , int y)
{
	if ( c == 'N' || c == 'W' || c == 'S' || c == 'E')
	{
		data->player->facing_dir = c;
		data->player->pos_x = x;
		data->player->pos_y = y;
		data->player->exists = 1;
	}
}

int is_valid_char(char c)
{
	if (c == '0' || c == '1')
		return 1;
	return 0;
}
