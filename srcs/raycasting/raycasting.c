#include "cube.h"


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

static void	find_hit_point(t_ray *ray, t_player *player, char **map, t_data *data)
{
	int	x;
	int	y;

	x = (int)player->pos_x;
	y = (int)player->pos_y;
	while(map[y][x] != '1')
	{
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
	draw_wall(x, y, ray, data);
}

void	raycasting(t_data *data, t_player *player, t_camera *camera)
{
	int				x;
	static t_ray	ray;
	double			camera_x;

	x = 0;
	setup_ray_casting(data, player, camera);
	player->pos_x += 0.5;
	player->pos_y += 0.5;
	while (x <= WIDTH)
	{
		camera_x = (2 * x) / (double)WIDTH - 1;
		ray.ray_x = player->dir_x + camera->plane_x * camera_x;
		ray.ray_y = player->dir_y + camera->plane_y * camera_x;
		set_ray(&ray, player);
		find_hit_point(&ray, player, data->map->map, data);
		x++;
	}
}