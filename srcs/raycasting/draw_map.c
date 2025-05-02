#include "cube.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;
	dst = data->img_addr + (y * data->line_length + x * (data->bits_per_pixel
		/ 8));
	*(unsigned int *)dst = color;
}

void	draw_background(t_data *data)
{
	int	height;
	int	width;

	height = 0;
	while (height < HEIGHT)
	{
		width = 0;
		while (width < WIDTH)
		{
			if (height >= HEIGHT / 2)
				my_mlx_pixel_put(data, width, height,  data->map->c_rgb);
			else
				my_mlx_pixel_put(data, width, height, data->map->f_rgb);
			width++;
		}
		height++;
	}
}