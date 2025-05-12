#include "cube.h"

unsigned int	get_color(t_ray *ray)
{
	unsigned int	color;

	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			color = 242 << 16 | 231 << 8 | 21;
		else
			color = 0x000000;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			color = 199 << 16 | 189 << 8 | 171;
		else
			color = 0 << 16 | 0 << 8 | 255;
	}
	return (color);
}

void	draw_wall(int x, int y, t_ray *ray, t_data *data)
{
	double			distance;
	int				height;
	int				i;
	int				k;
	unsigned int	color;

	i = 0;
	k = HEIGHT / 2;
	if (ray->side == 0)
		distance = (x - data->player->pos_x + (1 - ray->ray_dir_x) / 2) / ray->ray_x;
	else
		distance = (y - data->player->pos_y + (1 - ray->ray_dir_y) / 2) / ray->ray_y;
	height = (1000 / distance);
	ray->hitpoint_x = data->player->pos_x + (distance * ray->dist_x);
	ray->hitpoint_y = data->player->pos_y + (distance * ray->dist_y);
	color = get_color(ray);
	while (i < height / 2)
	{
		if ((k + i) < HEIGHT)
			my_mlx_pixel_put(data, ray->x, k + i, color);
		if ((k - i) > 0)
			my_mlx_pixel_put(data, ray->x, k - i, color);
		i++;
	}
	//create_texture(data, x, 0, ray);
}
