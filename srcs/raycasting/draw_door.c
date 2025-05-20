/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:37:14 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/05/20 14:37:16 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	add_list(t_list **rays, t_ray *ray, int x, int y)
{
	t_list	*node;
	t_ray	*ray_copy;

	ray_copy = copy_ray(ray);
	node = ft_lstnew(ray_copy);
	ray_copy->x_map = x;
	ray_copy->y_map = y;
	ft_lstadd_front(rays, node);
}

void	draw_door(t_list **rays, t_data *data)
{
	t_list	**copy;

	copy = rays;
	while (*rays)
	{
		draw_wall(((t_ray *)(*rays)->content)->x_map, ((t_ray *)(*rays)->content)->y_map, (t_ray *)((*rays)->content), data);
		*rays = (*rays)->next;
	}
	ft_lstclear(copy, free);
}