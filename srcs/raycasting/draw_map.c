#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
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
				my_mlx_pixel_put(data, width, height,  data->map->f_rgb);
			else
				my_mlx_pixel_put(data, width, height, data->map->c_rgb);
			width++;
		}
		height++;
	}
}

void	draw(t_data *data)
{
	draw_background(data);
	raycasting(data, data->player, data->camera, "1");
	raycasting(data, data->player, data->camera, "PO");
	draw_mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}