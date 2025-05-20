/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:41:27 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/05/15 15:52:53 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_texture	*choose_texture(t_ray *ray, t_data *data)
{
	t_texture	*texture;

	if (ray->identifier == 'P')
		texture = data->door[0];
	else if (ray->identifier == 'O')
		texture = data->door[3];
	else if (ray->identifier == 'D')
		texture = data->desk;
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
	return (texture);
}

unsigned int	get_color(t_ray *ray, t_data *data, int height, int y)
{
	unsigned int	color;
	t_texture		*texture;
	int				x;

	x = ray->x;
	texture = choose_texture(ray, data);
	x = (int)((ray->hitpoint_x - floor(ray->hitpoint_x))\
	* (double)texture->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		x = texture->width - x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		x = texture->width - x - 1;
	if (height != 0)
		y = y * texture->height / height;
	color = *(texture->img_ptr + (((((int)x % texture->width) + \
	((y % texture->height) * texture->width)))));
	return (color);
}

int	find_height(int x, int y, t_ray *ray, t_data *data)
{
	double			distance;
	int				height;
	double			delta_x;

	if (ray->side == 0)
	{
		distance = (x - data->player->pos_x + (1 - ray->ray_dir_x) / 2) \
		/ ray->ray_x;
		delta_x = ray->side_dist_x - ray->dist_x;
		ray->hitpoint_x = data->player->pos_y + (delta_x * ray->ray_y);
	}
	else
	{
		distance = (y - data->player->pos_y + (1 - ray->ray_dir_y) / 2) \
		/ ray->ray_y;
		delta_x = ray->side_dist_y - ray->dist_y;
		ray->hitpoint_x = data->player->pos_x + (delta_x * ray->ray_x);
	}
	height = (HEIGHT / distance);
	return (height);
}

void	draw_wall(int x, int y, t_ray *ray, t_data *data)
{
	int				i;
	int				k;
	int				height;
	unsigned int	color;

	i = 0;
	height = find_height(x, y, ray, data);
	k = (HEIGHT / 2) - (height / 2);
	if (k + i < 0)
		i = -k;
	while (i < height && (k + i) < HEIGHT)
	{
		color = get_color(ray, data, height, i);
		if ((color != 0xFFFFFF && \
		(ray->identifier == 'P' || ray->identifier == 'O')) || \
		(ray->identifier != 'P' && ray->identifier != 'O'))
			my_mlx_pixel_put(data, ray->x, k + i, color);
		i++;
	}
}
