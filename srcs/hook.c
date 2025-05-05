#include "cube.h"

int	key_hook(int keycode, t_data *data)
{
	printf("%d\n", keycode);
	if (keycode == 65362)
		data->player->facing_dir = 'N';
	if (keycode == 65364)
		data->player->facing_dir = 'S';
	if (keycode == 65361)
		data->player->facing_dir = 'W';
	if (keycode == 65363)
		data->player->facing_dir = 'E';
	if (keycode == 119)
		data->player->pos_y -= 0.1;
	if (keycode == 100)
		data->player->pos_x += 0.1;
	if (keycode == 115)
		data->player->pos_y += 0.1;
	if (keycode == 97)
		data->player->pos_x -= 0.1;
	draw_background(data);
	raycasting(data, data->player, data->camera);
	draw_mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}