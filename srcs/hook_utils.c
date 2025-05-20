/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:15:21 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/05/20 15:15:23 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_if_door(int x, int y, t_data *data)
{
	int			i;
	t_texture	*temp;

	i = 0;
	if (data->map->map[y][x] == 'P')
	{
		data->map->map[(int)y][(int)x] = 'O';
		temp = data->door[3];
		while (i < 3)
		{
			data->door[3] = data->door[i];
			draw(data);
			i++;
		}
		data->door[3] = temp;
		draw(data);
		return (1);
	}
	else if (data->map->map[(int)y][(int)x] == 'O')
	{
		data->map->map[(int)y][(int)x] = 'P';
		temp = data->door[0];
		i = 3;
		while (i >= 0)
		{
			data->door[0] = data->door[i];
			draw(data);
			i--;
		}
		data->door[0] = temp;
		draw(data);
		return (1);
	}
	return (0);
}

char	see_in_front(t_data *data)
{
	double	move_x;
	double	move_y;
	double	x;
	double	y;
	int		dist;

	move_x = (data->player->dir_x * 0.1);
	move_y = (data->player->dir_y * 0.1);
	x = data->player->pos_x + move_x;
	y = data->player->pos_y + move_y;
	dist = 0;
	while (dist < 12)
	{
		if (check_if_door(x, y, data) == 1)
			break ;
		x += move_x;
		y += move_y;
		dist++;
	}
	return (data->map->map[(int)move_y][(int)move_x]);
}
