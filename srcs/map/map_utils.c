#include "cube.h"

static void	check_player_surroundings(t_data *data, char **map, int x, int y);

int	check_zero_surroundings(char **tab, int x, int y)
{
	char	c_up;
	char	c_down;
	char	c_left;
	char	c_right;
	char	c_top_left;
	char	c_top_right;
	char	c_bottom_left;
	char	c_bottom_right;

	if (!is_coordinate_valid(tab, x, y))
		return (0);
	// Just setting everything to null
	c_up = '\0';
	c_down = '\0';
	c_left = '\0';
	c_right = '\0';
	c_top_left = '\0';
	c_top_right = '\0';
	c_bottom_left = '\0';
	c_bottom_right = '\0';
	// Coordinate checks
	if (is_coordinate_valid(tab, x, y - 1))
		c_up = tab[y - 1][x];
	if (is_coordinate_valid(tab, x, y + 1))
		c_down = tab[y + 1][x];
	if (is_coordinate_valid(tab, x - 1, y))
		c_left = tab[y][x - 1];
	if (is_coordinate_valid(tab, x + 1, y))
		c_right = tab[y][x + 1];
	if (is_coordinate_valid(tab, x - 1, y - 1))
		c_top_left = tab[y - 1][x - 1];
	if (is_coordinate_valid(tab, x + 1, y - 1))
		c_top_right = tab[y - 1][x + 1];
	if (is_coordinate_valid(tab, x - 1, y + 1))
		c_bottom_left = tab[y + 1][x - 1];
	if (is_coordinate_valid(tab, x + 1, y + 1))
		c_bottom_right = tab[y + 1][x + 1];
	if (are_sorroundings_valid(c_up) && are_sorroundings_valid(c_down)
		&& are_sorroundings_valid(c_left) && are_sorroundings_valid(c_right)
		&& are_sorroundings_valid(c_top_left)
		&& are_sorroundings_valid(c_top_right)
		&& are_sorroundings_valid(c_bottom_left)
		&& are_sorroundings_valid(c_bottom_right))
		return (1);
	return (0);
}

int	check_and_set(t_data *data, char c, int x, int y)
{
  char **map = data->map->map;
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
	{
		data->player->facing_dir = c;
		data->player->pos_x = x;
		data->player->pos_y = y;
		data->player->exists += 1;
		check_player_surroundings(data,map, x, y);
		return (1);
	}
	else if (c == '0' || c == '1' || c == '\n' || c == '\t' || c == ' ')
		return (1);
	return (0);
}

static void	check_player_surroundings(t_data *data, char **map, int x, int y)
{
	int	map_height;
	map_height = data->map->map_height;
	if ((y <= 0 || y - map_height >= (map_height - 1)
        || (map[y][x + 1] != '0' && map[y][x + 1] != '1')
        || (map[y][x - 1] != '0' && map[y][x - 1] != '1')
        || (map[y - 1][x] != '0' && map[y - 1][x] != '1')
        || (map[y + 1][x] != '0' && map[y + 1][x] != '1')
        || (map[y - 1][x - 1] != '0' && map[y - 1][x - 1] != '1')
        || (map[y - 1][x + 1] != '0' && map[y - 1][x + 1] != '1')
        || (map[y + 1][x - 1] != '0' && map[y + 1][x - 1] != '1')
        || (map[y + 1][x + 1] != '0' && map[y + 1][x + 1] != '1')))
	{
		printf("Player has no valid surroundings\n");
		exit(1);
	}
}

int	are_sorroundings_valid(char c)
{
	if (c == '0' || c == '1' || c == 'W' || c == 'N' || c == 'S' || c == 'E')
		return (1);
	return (0);
}

int	is_coordinate_valid(char **tab, int x, int y)
{
	if (tab && y >= 0 && x >= 0 && tab[y] && tab[y][x])
		return (1);
	return (0);
}
