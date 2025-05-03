#include "cube.h"

void	raycasting(t_data *data, t_player *player, t_camera *camera)
{
	int	x;
	double	ray_x;
	double	ray_y;
	double	camera_x;

	x = 0;
	setup_ray_casting(data, player, camera);
	while (x < (WIDTH))
	{
		camera_x = (2 * x) / (double)WIDTH - 1;
		ray_x = player->dir_x + camera->plane_x * camera_x;
		ray_y = player->dir_y + camera->plane_y * camera_x;
		find_hit_point(ray_x, ray_y, data);
		x++;
	}

}