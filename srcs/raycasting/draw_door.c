#include "cube.h"

unsigned int	get_color(t_ray *ray, t_data *data, int x, int y)
{
	unsigned int	color;

	color = *(data->map->door_txt_path[0] + (((x % data->map->door_txt_path[0]->width) + ((y % data->west->height) * data->west->width))));
	return (color);
}

void	draw_close_door(int x, int y, t_ray *ray, t_data *data)
{
	double			distance;
	int				height;
	int				i;
	int				k;
	// unsigned int	color;

	i = 0;
	k = HEIGHT / 2;
	if (ray->side == 0)
		distance = (x - data->player->pos_x + (1 - ray->ray_dir_x) / 2) / ray->ray_x;
	else
		distance = (y - data->player->pos_y + (1 - ray->ray_dir_y) / 2) / ray->ray_y;
	height = (HEIGHT / distance);
	ray->hitpoint_x = data->player->pos_x + (distance * ray->dist_x);
	ray->hitpoint_y = data->player->pos_y + (distance * ray->dist_y);
	// color = get_color(ray, data, k);
	while (i < height / 2)
	{
		if ((k + i) < HEIGHT)
			my_mlx_pixel_put(data, ray->x, k + i, get_color(ray, data, (ray->x * 0.08), (k + i) * 0.08));
		if ((k - i) > 0)
			my_mlx_pixel_put(data, ray->x, k - i, get_color(ray, data, (ray->x * 0.08), (k - i) * 0.08));
		i++;
	}
}