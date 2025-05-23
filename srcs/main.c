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
	parser(&data,&map,&player,av);
	rgb_converter(&data,'F');
	rgb_converter(&data,'C');
	data.mlx_ptr = mlx_init();
	create_img(&data);
	draw_background(&data);
	raycasting(&data, &player, &camera);
	draw_mini_map(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 0, 0);
	mlx_loop(data.mlx_ptr);
	return (0);
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
  printf("SO = %s\n",map->so_txt_path);
  printf("WE = %s\n",map->we_txt_path);
  printf("EA = %s\n",map->ea_txt_path);
  printf("CEILING = %s\n",map->ceiling_info);
  printf("FLOOR = %s\n",map->floor_info);
  printf("PLAYER X = %f\n",player->pos_x);
  printf("PLAYER Y = %f\n",player->pos_y);
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
