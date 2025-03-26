#include "cube.h"

char **fill_map(t_data *data)
{
	char **map;
	char *res;

	map = ft_calloc(1,sizeof(char *));
	if (!map)
	{
		ft_putstr_fd("Malloc error\n",2);
		return NULL;
	}
	while(1)
	{
		res = get_next_line(data->map_ptr);
		if (!res)
			break;
		map = ft_strscat(map,res);
		if (!map)
		{
			free_strs(map);
			return NULL;
		}
	}
	return map;
}

// void fill(char **tab, t_point size, char target, int row, int col)
// {
//     // Check if current row and column values are out of bounds
//     if (row < 0 || col < 0 || row >= size.y || col >= size.x)
//         return;
//     
//     // Check if current cell has already been filled or does not match the target character
//     if (tab[row][col] == 'F' || tab[row][col] != target)
//         return;
//
//     // Mark current cell as filled
//     tab[row][col] = 'F';
//
//     // Recursively fill neighboring cells
//     fill(tab, size, target, row -1, col); // fill cell above
//     fill(tab, size, target, row +1, col); // fill cell below
//     fill(tab, size, target, row, col - 1); // fill cell to the left
//     fill(tab, size, target, row, col + 1); // fill cell to the right
// }
//
// // Function to initiate flood fill from a specified point
// void flood_fill(char **tab, t_point size, t_point begin)
// {
//     char target = tab[begin.y][begin.x]; // Get the character to fill around
//     fill(tab, size, target, begin.y, begin.x); // Start the flood fill from the specified point
// }

int set_map_struct(t_data *data)
{
	char **map;
	int y = 0;
	int x = 0;
	
	y = 0;
	x = 0;
	map = data->map->map;
	while(map[y] && data->map->is_map_valid)
	{
		while(map[y][x])
		{
			if (is_valid_char(map[y][x]) == 0)
				data->map->is_map_valid = 0;
			detect_player(data,map[y][x],x,y);
			x++;
		}
		x = 0;
		y++;
	}
	if (data->player->exists == 0)
		data->map->is_map_valid = 0;
	return 0;
}

