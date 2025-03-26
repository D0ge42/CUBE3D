#include "cube.h"

/*static int create_img(t_data *data);*/
/*static void	my_mlx_pixel_put(t_data *data, int x, int y, int color);*/

int main()
{
	static t_data data;
	static t_map map;
	static t_player player;

	data.map_ptr = open("maps/map.cub",O_RDONLY);
	data.map = &map;
	data.player = &player;
	data.map->map = fill_map(&data);
	data.map->is_map_valid = 1;
	data.map = &map;
	if (set_map_struct(&data) == 0)
		printf("Map not valid\n");
	print_map(map.map);
	/*data.mlx_ptr = mlx_init();*/
	/*map_checker(&data);*/
	/*create_img(&data);*/
	/*my_mlx_pixel_put(&data,500,500,0x00FF0000);*/
	/*mlx_put_image_to_window(data.mlx_ptr,data.win_ptr,data.img,0,0);*/
	/*mlx_loop(data.mlx_ptr);*/
	return 0;
}

/*static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)*/
/*{*/
/*	char	*dst;*/
/**/
/*	dst = data->img_addr + (y * data->line_length + x * (data->bits_per_pixel / 8));*/
/*	*(unsigned int*)dst = color;*/
/*}*/
/**/
/*static int create_img(t_data *data)*/
/*{*/
/*	if (!data->mlx_ptr)*/
/*		return 0;*/
/*	data->win_ptr = mlx_new_window(data->mlx_ptr,WIDTH,HEIGHT,"CUBE3D");*/
/*	if (!data->win_ptr)*/
/*		return 0;*/
/*	data->img = mlx_new_image(data->mlx_ptr,WIDTH,HEIGHT);*/
/*	if (!data->img)*/
/*		return 0;*/
/*	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,*/
/*									&data->line_length, &data->endian);*/
/*	return 1;*/
/*}*/

