#include "cube.h"
#include "libft.h"
#include <fcntl.h>

int main()
{
	int i = 4;
	int fd = open("srcs/testfile",O_RDONLY);
	while(i)
	{
		printf("%s\n",get_next_line(fd));
		i--;
	}
}
/*static int create_img(t_data *data);*/
/*static void	my_mlx_pixel_put(t_data *data, int x, int y, int color);*/
/*static  int map_checker(t_data *data);*/
/**/
/**/
/*int main()*/
/*{*/
/*	t_data data;*/
/**/
/*	data.map_ptr = open("../maps/map.cub",O_RDONLY);*/
/*	data.mlx_ptr = mlx_init();*/
/*	map_checker(&data);*/
/*	create_img(&data);*/
/*	my_mlx_pixel_put(&data,500,500,0x00FF0000);*/
/*	mlx_put_image_to_window(data.mlx_ptr,data.win_ptr,data.img,0,0);*/
/*	mlx_loop(data.mlx_ptr);*/
/*	return 0;*/
/*}*/
/**/
/*static  int map_checker(t_data *data)*/
/*{*/
/*	(void)data;*/
/*	printf("ciao");*/
/*	return 0;*/
/*}*/
/**/
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


