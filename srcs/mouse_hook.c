#include "cube.h"

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	(void) y;
	printf("%d\n", keycode);
	if ((x < WIDTH / 2 && keycode == 1) || keycode == 4)
		rotate_player(65361, data);
	else if (keycode == 1 || keycode == 5)
		rotate_player(65363, data);
	draw_background(data);
	raycasting(data, data->player, data->camera);
	draw_mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}