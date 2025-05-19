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

unsigned int	get_color(t_ray *ray, t_data *data, int height, int y)
{
	unsigned int	color;
	t_texture		*texture;
	int				x;

	x = ray->x;
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
	x = (int)(((ray->hitpoint_x - floor(ray->hitpoint_x))) * (double)texture->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		x = texture->width - x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		x = texture->width - x - 1;
	if (height != 0)
		y = y * texture->height / height;
	color = *(texture->img_ptr + (((((int)x % texture->width) + ((y % texture->height) * texture->width)))));
	return (color);
}

void	draw_wall(int x, int y, t_ray *ray, t_data *data)
{
	double			distance;
	int				height;
	int				i;
	int				k;
	double			prova;
	unsigned int	color;

	i = 0;

	if (ray->side == 0)
		distance = (x - data->player->pos_x + (1 - ray->ray_dir_x) / 2) / ray->ray_x;
	else
		distance = (y - data->player->pos_y + (1 - ray->ray_dir_y) / 2) / ray->ray_y;
	if (ray->side == 0)
	{
		prova = ray->side_dist_x - ray->dist_x;
		ray->hitpoint_x = data->player->pos_y + (prova * ray->ray_y);
	}
	else
	{
		prova = ray->side_dist_y - ray->dist_y;
		ray->hitpoint_x = data->player->pos_x + (prova * ray->ray_x);
	}
	printf("%f\n", distance);
	height = (HEIGHT / distance);
	k = (HEIGHT / 2) - (height / 2);
	if (k + i < 0)
		i = -k;
	while (i < height && (k + i) < HEIGHT)
	{
		color = get_color(ray, data, height, i);
		if ((color != 0xFFFFFF && (ray->identifier == 'P' || ray->identifier == 'O')) || (ray->identifier != 'P' && ray->identifier != 'O'))
			my_mlx_pixel_put(data, ray->x, k + i, color);
		i++;
	}
}
