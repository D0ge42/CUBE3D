/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:45:16 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/05/23 16:45:25 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_textures(t_data *data, int i)
{
	if (i > 0)
		if (data->nord)
			mlx_destroy_image(data->mlx_ptr, data->nord->img);
	if (i > 1)
		if (data->sud)
			mlx_destroy_image(data->mlx_ptr, data->sud->img);
	if (i > 2)
		if (data->est)
			mlx_destroy_image(data->mlx_ptr, data->est->img);
	if (i > 3)
		if (data->west)
			mlx_destroy_image(data->mlx_ptr, data->west->img);
	if (i > 4)
		if (data->door[0])
			mlx_destroy_image(data->mlx_ptr, data->door[0]->img);
	if (i > 5)
		if (data->door[1])
			mlx_destroy_image(data->mlx_ptr, data->door[1]->img);
	if (i > 6)
		if (data->door[2])
			mlx_destroy_image(data->mlx_ptr, data->door[2]->img);
	if (i > 7)
		if (data->door[3])
			mlx_destroy_image(data->mlx_ptr, data->door[3]->img);
}

void	set_pointer(t_texture *texture, t_texture **txt_data, t_data *data,
		int *i)
{
	if (texture->img == NULL)
	{
		data->err_type = E_INV_TEX;
		free_textures(data, *i);
		print_err_and_free(data, NULL);
	}
	*i = *i + 1;
	texture->img_ptr = (unsigned *)mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_lenght, &texture->endian);
	*txt_data = texture;
}

void	set_wall_texture(t_data *data, int *i)
{
	static t_texture	nord;
	static t_texture	sud;
	static t_texture	est;
	static t_texture	west;

	nord.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->no_txt_path,
			&nord.width, &nord.height);
	sud.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->so_txt_path,
			&sud.width, &sud.height);
	est.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->ea_txt_path,
			&est.width, &est.height);
	west.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->we_txt_path,
			&west.width, &west.height);
	set_pointer(&nord, &data->nord, data, i);
	set_pointer(&sud, &data->sud, data, i);
	set_pointer(&est, &data->est, data, i);
	set_pointer(&west, &data->west, data, i);
}

void	set_texture(t_data *data)
{
	static t_texture	door[4];
	static t_texture	desk;
	int					i;

	set_wall_texture(data, &i);
	door[0].img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map->door_txt_path[0], &door[0].width, &door[0].height);
	door[1].img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map->door_txt_path[1], &door[1].width, &door[1].height);
	door[2].img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map->door_txt_path[2], &door[2].width, &door[2].height);
	door[3].img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map->door_txt_path[3], &door[3].width, &door[3].height);
	desk.img = mlx_xpm_file_to_image(data->mlx_ptr,
			"./srcs/sprites/cube3dtex/xpm/scrivania.xpm", &desk.width, &desk.height);
	set_pointer(&door[0], &data->door[0], data, &i);
	set_pointer(&door[1], &data->door[1], data, &i);
	set_pointer(&door[2], &data->door[2], data, &i);
	set_pointer(&door[3], &data->door[3], data, &i);
	set_pointer(&desk, &data->desk, data, &i);
}
