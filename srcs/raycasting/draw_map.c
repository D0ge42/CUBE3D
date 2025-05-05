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

void	draw_wall(int x, int y, t_ray *ray, t_data *data)
{
	t_map	*map;
	double	distance;
	int		height;
	int		i;
	int		k;
	unsigned int	color;

	map = data->map;
	i = 0;
	k = HEIGHT / 2;
	if (ray->side == 0)
		distance = (x - data->player->pos_x + (1 - ray->ray_dir_x) / 2) / ray->ray_x;
	else
		distance = (y - data->player->pos_y + (1 - ray->ray_dir_y) / 2) / ray->ray_y;
	height = (1000 / distance);
	if (ray->side == 0)
		color = 0xFFFF00;
	else
		color = 0x000000;
	while (i < height / 2)
	{
		if ((k + i) < HEIGHT)
			my_mlx_pixel_put(data, ray->x, k + i, color);
		if ((k - i) > 0)
			my_mlx_pixel_put(data, ray->x, k - i, color);
		i++;
	}
	fill_square(x * 10, (y - map->map_start) * 10, data, 0xFFFF00);
}