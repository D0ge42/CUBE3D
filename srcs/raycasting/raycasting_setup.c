#include "cube.h"

void setup_ray_casting(t_data *data, t_player *player,t_camera *camera)
{
	(void)data;
	player->dir_x = -1;
	player->dir_y = 0;
	camera->plane_x = 0;
	camera->plane_y = 0.66;

}
