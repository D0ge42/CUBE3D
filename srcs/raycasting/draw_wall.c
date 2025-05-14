#include "cube.h"

unsigned int	get_color(t_ray *ray, t_data *data, int height, int y)
{
	unsigned int	color;
	t_texture		*texture;
	double				x;

	printf("%f\n", ray->hitpoint_x);
	if (ray->identifier == 'P')
		texture = data->door[0];
	else if (ray->identifier == 'O')
		texture = data->door[3];
	else if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			texture = data->west;
		else
			texture = data->est;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			texture = data->sud;
		else
			texture = data->nord;
	}
	x = (ray->hitpoint_x - floor(ray->hitpoint_x)) * 10;
	// printf("%f %f\n", x, ray->hitpoint_x);
	if (height != 0)
		y = y * texture->height / height;
	color = *(texture->img_ptr + ((((int)x % texture->width) + ((y % texture->height) * texture->width))));
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

	if (ray->side == 0)
		distance = (x - data->player->pos_x + (1 - ray->ray_dir_x) / 2) / ray->ray_x;
	else
		distance = (y - data->player->pos_y + (1 - ray->ray_dir_y) / 2) / ray->ray_y;
	height = (HEIGHT / distance);
	k = (HEIGHT / 2) - (height / 2);
	ray->hitpoint_x = data->player->pos_x + (distance * ray->dist_x);
	ray->hitpoint_y = data->player->pos_y + (distance * ray->dist_y);
	//printf("%f\n", ray->hitpoint_x);
	if (k + i < 0)
		i = -k;
	while (i < height && (k + i) < HEIGHT)
	{
		color = get_color(ray, data, height, i);
		my_mlx_pixel_put(data, ray->x, k + i, color);
		i++;
	}
}
