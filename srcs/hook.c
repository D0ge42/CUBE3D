#include "cube.h"

static void	find_direction(t_player *player)
{
	if (player->dir_x <= 0 && player->dir_y <= 0)
		player->facing_dir = 'W';
	if (player->dir_x <= 0 && player->dir_y >= 0)
		player->facing_dir = 'N';
	if (player->dir_x >= 0 && player->dir_y >= 0)
		player->facing_dir = 'E';
	if (player->dir_x >= 0 && player->dir_y <= 0)
		player->facing_dir = 'S';
}

static void	move_player(int keycode, t_data *data)
{
	if (keycode == 119)
	{
		data->player->pos_x -= (data->player->dir_x * 0.1 + (0.1 - data->player->dir_x));
		data->player->pos_y -= (data->player->dir_y * 0.1 + (0.1 - data->player->dir_y));
	}
	if (keycode == 100)
		data->player->pos_x -= (data->player->dir_x * 0.1 + (0.1 - data->player->dir_x));
	if (keycode == 115)
	{
		data->player->pos_x += (data->player->dir_x * 0.1 + (0.1 - data->player->dir_x));
		data->player->pos_y += (data->player->dir_y * 0.1 + (0.1 - data->player->dir_y));
	}
	if (keycode == 97)
		data->player->pos_x += (data->player->dir_x * 0.1 + (0.1 - data->player->dir_x));
}

static void	rotate_player(int keycode, t_data *data)
{
	find_direction(data->player);
	if ((keycode == 65361 && data->player->facing_dir == 'N') || (keycode == 65363 && data->player->facing_dir == 'S'))
	{
		data->player->dir_x += 0.1;
		data->player->dir_y += 0.1;
	}
	if ((keycode == 65361 && data->player->facing_dir == 'E') || (keycode == 65363 && data->player->facing_dir == 'W'))
	{
		data->player->dir_x += 0.1;
		data->player->dir_y -= 0.1;
	}
	if ((keycode == 65361 && data->player->facing_dir == 'S') || (keycode == 65363 && data->player->facing_dir == 'N'))
	{
		data->player->dir_x -= 0.1;
		data->player->dir_y -= 0.1;
	}
	if ((keycode == 65361 && data->player->facing_dir == 'W') || (keycode == 65363 && data->player->facing_dir == 'E'))
	{
		data->player->dir_x -= 0.1;
		data->player->dir_y += 0.1;
	}
}

int	key_hook(int keycode, t_data *data)
{
	printf("%d\n", keycode);
	rotate_player(keycode, data);
	move_player(keycode, data);
	draw_background(data);
	raycasting(data, data->player, data->camera);
	draw_mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}