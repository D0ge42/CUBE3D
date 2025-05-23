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
	//char	**map;
	double		distance;
	int			i;

	(void) ray;
	i = 0;
	//map = data->map->map;
	if (ray->side == 0)
		distance = (x - data->player->pos_x + (1 - ray->ray_dir_x) / 2) / ray->ray_x;
	else
		distance = (y - data->player->pos_y + (1 - ray->ray_dir_y) / 2) / ray->ray_y;
	distance *= 30;
	while (i < distance && i < HEIGHT)
	{
		my_mlx_pixel_put(data, x * 30, (y * 30) + i, 0xFFFFFF);
		i++;
	}
}