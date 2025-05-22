/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:46:35 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/05/19 19:46:39 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	define_values(t_minimap *minimap, t_data *data)
{
	minimap->start_x = data->player->pos_x - 10;
	if (minimap->start_x < 0)
		minimap->start_x = 0;
	minimap->start_y = data->player->pos_y - data->map->map_start - 10;
	if (minimap->start_y < 0)
		minimap->start_y = 0;
	minimap->end_x = data->player->pos_x + 10;
	if (minimap->end_x > data->map->map_width)
		minimap->end_x = data->map->map_width;
	minimap->end_y = data->player->pos_y - data->map->map_start + 10;
	if (minimap->end_y > data->map->map_height)
		minimap->end_y = data->map->map_height;
}

void	fill_square(int x, int y, t_data *data, int color)
{
	int		len;
	int		height;

	height = 0;
	while (height < 10)
	{
		len = 0;
		while (len < 10)
		{
			if ((WIDTH - 210 + x + len) < WIDTH && (WIDTH - 210 + x + len) > 0 && (HEIGHT - 210 + y + height) < HEIGHT && (HEIGHT - 210 + y + height) > 0)
				my_mlx_pixel_put(data, (WIDTH - (210) + x + len), HEIGHT - 210 + y + height, color);
			len++;
		}
		height++;
	}
}

void	draw_mini_map(t_data *data)
{
	char				**map;
	static t_minimap	minimap;
	int					temp_x;
	int					temp_y;

	map = data->map->map + data->map->map_start;
	define_values(&minimap, data);

	temp_y = minimap.start_y;
	while(map[temp_y] && temp_y < minimap.end_y && temp_y < HEIGHT)
	{
		temp_x = minimap.start_x;
		while (map[temp_y][temp_x] && temp_x < minimap.end_x && temp_x < WIDTH)
		{
			if (map[temp_y][temp_x] == '1')
				fill_square((temp_x - minimap.start_x) * 10, (temp_y - minimap.start_y) * 10, data, 0xFFFFFF);
			else if (map[temp_y][temp_x] != ' ' && map[temp_y][temp_x] != '\n')
				fill_square((temp_x - minimap.start_x) * 10, (temp_y - minimap.start_y) * 10, data, 0x000000);
			temp_x++;
		}
		temp_y++;
	}
	fill_square((data->player->pos_x - minimap.start_x) * 10, (data->player->pos_y - data->map->map_start - minimap.start_y) * 10, data, 0xFFFF00);
}
