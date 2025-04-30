#include "cube.h"

static int	create_img(t_data *data);
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
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
	parser(&data,&map,&player,av);
	setup_ray_casting(&data, &player, &camera);

	//game_loop(&data, &player, &map, &camera);
	data.mlx_ptr = mlx_init();
	create_img(&data);
	my_mlx_pixel_put(&data, 500, 500, 0x00FF0000);
	draw_background(&data);
	draw_mini_map(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 0, 0);
	mlx_loop(data.mlx_ptr);
	return (0);
}

static void parser(t_data *data, t_map *map, t_player *player, char **av)
{
	set_pointers(data, map, player, av);
	is_map_valid(data);
	is_map_closed(data);
	print_strs(data->map->map);
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

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->img_addr + (y * data->line_length + x * (data->bits_per_pixel
		/ 8));
	*(unsigned int *)dst = color;
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
