#include "cube.h"

unsigned int	get_color(t_ray *ray, t_data *data, int x, int y)
{
	unsigned int	color;

	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			color = *(data->west->img_ptr + (((x % data->west->width) + ((y % data->west->height) * data->west->width))));
		else
			color = *(data->est->img_ptr + ((x % data->est->width) + ((y % data->est->height) * data->est->width)));
	}
	else
	{
		if (ray->ray_dir_y > 0)
			color = *(data->sud->img_ptr + ((x % data->sud->width) + ((y % data->sud->height) * data->sud->width)));
		else
			color = *(data->nord->img_ptr + (((x % data->nord->width) + ((y % data->nord->height) * data->nord->width))));
	}
	return (color);
}

void	draw_wall(int x, int y, t_ray *ray, t_data *data)
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
	//create_texture(data, x, 0, ray);
}
