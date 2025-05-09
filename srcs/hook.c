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

static void	move_player(int keycode, t_data *data, t_map *map)
{
	double	move_x;
	double	move_y;
	double	temp_x;
	double	temp_y;

	move_x = (data->player->dir_x * 0.1);
	move_y = (data->player->dir_y * 0.1);
	if (keycode == 'w')
	{
		temp_x = data->player->pos_x + move_x;
		temp_y = data->player->pos_y + move_y;
	}
	if (keycode == 'a')
	{
		temp_x = data->player->pos_x + move_y;
		temp_y = data->player->pos_y - move_x;
	}
	if (keycode == 's')
	{
		temp_x = data->player->pos_x - move_x;
		temp_y = data->player->pos_y - move_y;
	}
	if (keycode == 'd')
	{
		temp_x = data->player->pos_x - move_y;
		temp_y = data->player->pos_y + move_x;
	}
	if (map->map[(int)temp_y][(int)temp_x] && map->map[(int)temp_y][(int)temp_x] != '1' && map->map[(int)temp_y][(int)temp_x] != ' ' && map->map[(int)temp_y][(int)temp_x] != '\n' && map->map[(int)temp_y][(int)temp_x] != '\0')
	{
		data->player->pos_x = temp_x;
		data->player->pos_y = temp_y;
		draw(data);
	}
}

int	rotate_player(int keycode, t_data *data)
{
	find_direction(data->player);
	if ((keycode == 65361 && data->player->facing_dir == 'N') || (keycode == 65363 && data->player->facing_dir == 'S'))
	{
		data->player->dir_x += 0.1;
		data->player->dir_y += 0.1;
	}
	else if ((keycode == 65361 && data->player->facing_dir == 'E') || (keycode == 65363 && data->player->facing_dir == 'W'))
	{
		data->player->dir_x += 0.1;
		data->player->dir_y -= 0.1;
	}
	else if ((keycode == 65361 && data->player->facing_dir == 'S') || (keycode == 65363 && data->player->facing_dir == 'N'))
	{
		data->player->dir_x -= 0.1;
		data->player->dir_y -= 0.1;
	}
	else if ((keycode == 65361 && data->player->facing_dir == 'W') || (keycode == 65363 && data->player->facing_dir == 'E'))
	{
		data->player->dir_x -= 0.1;
		data->player->dir_y += 0.1;
	}
	else
		return (0);
	return (1);
}

int	key_hook(int keycode, t_data *data)
{
	printf("%d\n", keycode);
	if (keycode == XK_Escape)
	{
		free_everything(data);
		exit(0);
	}
	if (rotate_player(keycode, data) == 1)
		draw(data);
	if (keycode == 'w' || keycode == 'd' || keycode == 's' || keycode == 'a')
	{
		move_player(keycode, data, data->map);
		return (0);
	}
	return (0);
}