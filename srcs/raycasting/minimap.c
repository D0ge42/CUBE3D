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
	char	**map;
	int		m_start_x;
	int		m_start_y;
	int		m_end_x;
	int		m_end_y;
	int		temp_x;
	int		temp_y;

	map = data->map->map + data->map->map_start;
	m_start_x = data->player->pos_x - 10;
	if (m_start_x < 0)
		m_start_x = 0;
	m_start_y = data->player->pos_y - data->map->map_start - 10;
	if (m_start_y < data->map->map_start)
		m_start_y = 0;
	m_end_x = data->player->pos_x + 10;
	if (m_end_x > data->map->map_width)
		m_end_x = data->map->map_width;
	m_end_y = data->player->pos_y - data->map->map_start + 10;
	if (m_end_y > data->map->map_height)
		m_end_y = data->map->map_height;
	temp_y = m_start_y;
	while(map[temp_y] && temp_y < m_end_y && temp_y < HEIGHT)
	{
		temp_x = m_start_x;
		while (map[temp_y][temp_x] && temp_x < m_end_x && temp_x < WIDTH)
		{
			if (map[temp_y][temp_x] == '1')
				fill_square((temp_x - m_start_x) * 10, (temp_y - m_start_y) * 10, data, 0xFF0000);
			else if (map[temp_y][temp_x] != ' ' && map[temp_y][temp_x] != '\n')
				fill_square((temp_x - m_start_x) * 10, (temp_y - m_start_y) * 10, data, 0x000000);
			temp_x++;
		}
		temp_y++;
	}
	fill_square((data->player->pos_x - m_start_x) * 10, (data->player->pos_y - data->map->map_start - m_start_y) * 10, data, 0xFFFF00);
}
