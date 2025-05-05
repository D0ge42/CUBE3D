#include "cube.h"

void	setup_direction(t_player *player)
{
	if (player->facing_dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (player->facing_dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (player->facing_dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
}

void setup_ray_casting(t_data *data, t_player *player,t_camera *camera)
{
	(void) data;
	camera->plane_x = -(player->dir_y) * 0.66;
	camera->plane_y = player->dir_x * 0.66;
}
