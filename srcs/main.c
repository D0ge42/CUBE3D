#include "cube.h"

static int	create_img(t_data *data);
//static void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
static void	set_pointers(t_data *data, t_map *map, t_player *player, char **av);
static void	check_format(char *arg);
static void parser(t_data *data, t_map *map, t_player *player, char **av);

int	main(int ac, char **av)
{
	static t_data	data;
	static t_map	map;
	static t_player	player;
	static t_camera	camera;

	if (ac != 2)
    return (0);
	data.camera = &camera;
	parser(&data,&map,&player,av);
	rgb_converter(&data,'F');
	rgb_converter(&data,'C');
	data.mlx_ptr = mlx_init();
	create_img(&data);
	setup_direction(&player);
	set_texture(&data);
	draw(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_hook(data.win_ptr, 17, 0L, free_exit, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

void	set_texture(t_data *data)
{
	static t_texture	nord;
	static t_texture	sud;
	static t_texture	est;
	static t_texture	west;

	nord.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->no_txt_path, &nord.width, &nord.height);
	sud.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->so_txt_path, &sud.width, &sud.height);
	est.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->ea_txt_path, &est.width, &est.height);
	west.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->we_txt_path, &west.width, &west.height);
	if (nord.img == NULL || sud.img == NULL || est.img == NULL || west.img == NULL)
	{
		printf("\ntexture not found\n");
		return ;
	}
	nord.img_ptr = (unsigned int *)mlx_get_data_addr(nord.img, &nord.bits_per_pixel, &nord.line_lenght, &nord.endian);
	sud.img_ptr = (unsigned *)mlx_get_data_addr(sud.img, &sud.bits_per_pixel, &sud.line_lenght, &sud.endian);
	est.img_ptr = (unsigned *)mlx_get_data_addr(est.img, &est.bits_per_pixel, &est.line_lenght, &est.endian);
	west.img_ptr = (unsigned *)mlx_get_data_addr(west.img, &west.bits_per_pixel, &west.line_lenght, &west.endian);
	data->nord = &nord;
	data->sud = &sud;
	data->est = &est;
	data->west = &west;
	// color = *(text_addr + (x * size_line + y * (bits / 8)));
	// printf("COLOR = %i\n",color);
	//color = *(text_addr + (int)(texture_width * (ray->hitpoint_x - (int)ray->hitpoint_x) + (texture_width * ((ray->hitpoint_y - (int)ray->hitpoint_y) * 10))));
	// fill_square(0, 0, data, color);
	//mlx_destroy_image(data->mlx_ptr, texture);
}

static void parser(t_data *data, t_map *map, t_player *player, char **av)
{
	set_pointers(data, map, player, av);
  extract_map_only(data);
  get_map_infos(data);
	is_map_closed(data);
	is_map_valid(data);
  printf("MAP_HEIGHT = %i\n",map->map_height);
  printf("MAP_START = %i\n",map->map_start);
  printf("MAP_WIDTH = %i\n",map->map_width);
  printf("NO = %s\n",map->no_txt_path);
  printf("SO = %s\n",map->so_txt_path); // ---> invalid read of size 1
  printf("WE = %s\n",map->we_txt_path);
  printf("EA = %s\n",map->ea_txt_path); // --> invalid read of size 1
  printf("CEILING = %s\n",map->ceiling_info);
  printf("FLOOR = %s\n",map->floor_info);
  printf("PLAYER X = %f\n",player->pos_x);
  printf("PLAYER Y = %f\n",player->pos_y);
  ft_print_rgb(&data->map->c_rgb);
  ft_print_rgb(&data->map->f_rgb);
  print_strs(&data->map->map[map->map_start]);

    // Free memory
  //free_everything(data);

}

static void	set_pointers(t_data *data, t_map *map, t_player *player, char **av)
{
	check_format(av[1]);
	data->map_ptr = open(av[1], O_RDONLY);
	if (data->map_ptr == -1)
	{
		printf("Error: couldn't open map\n");
		exit(1);
	}
	data->player = player;
	data->map = map;
	data->map->map = fill_map(data);
	data->map->door_txt_path[0] = "srcs/sprites/cub3dtex/xpm/door1.xpm";
	data->map->door_txt_path[1] = "srcs/sprites/cub3dtex/xpm/door2.xpm";
	data->map->door_txt_path[2] = "srcs/sprites/cub3dtex/xpm/door3.xpm";
	data->map->door_txt_path[3] = "srcs/sprites/cub3dtex/xpm/door4.xpm";
	data->map->is_map_valid = 1;
}

static void	check_format(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
		i++;
	while (i > 0)
	{
		if (arg[i] == '.')
			break ;
		i--;
	}
	if (ft_strncmp(&arg[i], ".cub", 5))
	{
		printf("Error: Format not valid\n");
		exit(1);
	}
}

static int	create_img(t_data *data)
{
	if (!data->mlx_ptr)
 		return (0);
 	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "CUBE3D");
	if (!data->win_ptr)
		return (0);
 	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
 	if (!data->img)
		return (0);
 	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
 			&data->line_length, &data->endian);
	return (1);
}
