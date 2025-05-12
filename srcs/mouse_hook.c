#include "cube.h"

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	int	code;

	code = 0;
	(void) y;
	if ((x < WIDTH / 2 && keycode == 1) || keycode == 4)
		code = rotate_player(65361, data);
	else if (keycode == 1 || keycode == 5)
		code = rotate_player(65363, data);
	if (code)
		draw(data);
	return (0);
}