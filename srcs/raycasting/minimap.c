#include "cube.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_addr + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	fill_square(int x, int y, t_data *data, int color)
{
	t_map	*map;
	int		len;
	int		height;

	height = 0;
	map = data->map;
	while (height < 10)
	{
		len = 0;
		while (len < 10)
		{
			my_mlx_pixel_put(data, (WIDTH - (map->map_width * 10)) + x + len, HEIGHT - (map->map_height * 10) + y + height, color);
			len++;
		}
		height++;
	}
}
void	draw_mini_map(t_data *data)
{
	char	**map;
	int		len;
	int		height;

	map = data->map->map;
	height = 0;
	while(map[height])
	{
		len = 0;
		while (map[height][len])
		{
			if (map[height][len] == '1')
				fill_square(len * 10, height * 10, data, 0x00FF0000);
			else if (map[height][len] == '0')
				fill_square(len * 10, height * 10, data, 0x000000);
			else if (map[height][len] != ' ' && map[height][len] != '\n')
				fill_square(len * 10, height * 10, data, 0xFFFF00);
			len++;
		}
		height++;
	}
}