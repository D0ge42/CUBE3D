#include "cube.h"

// static void	set_coordinate(int)
void	fill_square(int x, int y, t_data *data, int color)
{
	t_map	*map;
	int		len;
	int		height;

	height = 0;
	map = data->map;
	printf("%d\n", map->map_width);
	while (height < 10)
	{
		len = 0;
		while (len < 10)
		{
			my_mlx_pixel_put(data, (WIDTH - map->map_width * 10) + x + len, HEIGHT - map->map_height * 10 + y + height, color);
			len++;
		}
		height++;
	}
}
void	draw_mini_map(t_data *data)
{
	char	**map;
	int		m_start_x;
	int		m_start_y;
	int		m_end_x;
	int		m_end_y;
	int		temp_x;

	map = data->map->map + data->map->map_start;
	m_start_x = data->player->pos_x - 5;
	if (m_start_x < 0)
		m_start_x = 0;
	m_start_y = data->player->pos_y - data->map->map_start - 5;
	if (m_start_y < data->map->map_start)
		m_start_y = 0;
	m_end_x = data->player->pos_x + 5;
	if (m_end_x > data->map->map_width)
		m_end_x = data->map->map_width;
	m_end_y = data->player->pos_y + 5;
	if (m_end_y > data->map->map_height)
		m_end_y = data->map->map_height;
	while(map[m_start_y] && m_start_y < m_end_y && m_start_y < HEIGHT)
	{
		temp_x = m_start_x;
		while (map[m_start_y][temp_x] && temp_x < m_end_x && temp_x < WIDTH)
		{
			if (map[m_start_y][temp_x] == '1')
				fill_square(temp_x * 10, m_start_y * 10, data, 0x00FF0000);
			else if (map[m_start_y][temp_x] != ' ' && map[m_start_y][temp_x] != '\n')
				fill_square(temp_x * 10, m_start_y * 10, data, 0x000000);
			temp_x++;
		}
		m_start_y++;
	}
	fill_square(data->player->pos_x * 10, (data->player->pos_y - data->map->map_start) * 10, data, 0xFFFF00);
}