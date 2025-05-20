#include "cube.h"

t_ray	*copy_ray(t_ray *old)
{
	t_ray	*copy;

	copy = calloc(1, sizeof(t_ray));
	copy->x = old->x;
	copy->hitpoint_x = old->hitpoint_x;
	copy->hitpoint_y = old->hitpoint_y;
	copy->ray_y = old->ray_y;
	copy->ray_x = old->ray_x;
	copy->dist_x = old->dist_x;
	copy->dist_y = old->dist_y;
	copy->side_dist_x = old->side_dist_x;
	copy->side_dist_y = old->side_dist_y;
	copy->ray_dir_x = old->ray_dir_x;
	copy->ray_dir_y = old->ray_dir_y;
	copy->side = old->side;
	copy->identifier = old->identifier;
	return (copy);
}

int	check_identifier(char map, char *identifier)
{
	while (identifier && *identifier)
	{
		if (map == *identifier)
			return (0);
		identifier++;
	}
	return (1);
}

static void	set_ray(t_ray	*ray, t_player *player)
{
	ray->dist_x = fabs(1 / ray->ray_x);
	ray->dist_y = fabs(1 / ray->ray_y);
	if (ray->ray_x < 0)
	{
		ray->ray_dir_x = -1;
		ray->side_dist_x = (player->pos_x - (int)player->pos_x) * ray->dist_x;
	}
	else
	{
		ray->ray_dir_x = 1;
		ray->side_dist_x = ((int)player->pos_x + 1 - player->pos_x) * ray->dist_x;
	}
	if (ray->ray_y < 0)
	{
		ray->ray_dir_y = -1;
		ray->side_dist_y = (player->pos_y - (int)player->pos_y) * ray->dist_y;
	}
	else
	{
		ray->ray_dir_y = 1;
		ray->side_dist_y = ((int)player->pos_y + 1 - player->pos_y) * ray->dist_y;
	}
}

static void	find_hit_point(t_ray *ray, char **map, t_data *data, char *identifier)
{
	int			x;
	int			y;
	t_list		**rays;

	x = (int)data->player->pos_x;
	y = (int)data->player->pos_y;
	rays = calloc(1, sizeof(t_list *));
	while(map[y][x] != '1')
	{
		if (check_identifier(map[y][x], identifier) == 0)
		{
			ray->identifier = map[y][x];
			add_list(rays, ray, x, y);
		}
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->dist_x;
			x += ray->ray_dir_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->dist_y;
			y += ray->ray_dir_y;
			ray->side = 1;
		}
	}
	ray->identifier = map[y][x];
	draw_wall(x, y, ray, data);
	draw_door(rays, data);
	// while (*rays)
	// {
	// 	draw_wall(((t_ray *)(*rays)->content)->x_map, ((t_ray *)(*rays)->content)->y_map, (t_ray *)((*rays)->content), data);
	// 	*rays = (*rays)->next;
	// }
	//ft_lstclear(rays, free);
}

void	raycasting(t_data *data, t_player *player, t_camera *camera, char *identifier)
{
	int				x;
	static t_ray	ray;
	double			camera_x;

	x = 0;
	setup_ray_casting(data, player, camera);
	while (x <= WIDTH)
	{
		ray.x = x;
		camera_x = (2 * x) / (double)WIDTH - 1;
		ray.ray_x = player->dir_x + camera->plane_x * camera_x;
		ray.ray_y = player->dir_y + camera->plane_y * camera_x;
		set_ray(&ray, player);
		find_hit_point(&ray, data->map->map, data, identifier);
		x++;
	}
}
