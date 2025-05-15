#include "cube.h"
#include "libft.h"
#include <stdlib.h>

static void	check_color_validity(t_data *data, char *str, unsigned int *rgb,
				char **tmp_color);
static void	check_overflow(t_data *data, char *str);
void print_err_and_free(t_data *data, void *ptr);

void	rgb_converter(t_data *data, char x)
{
	char			*str;
	unsigned int	*rgb;
	int				i;
	int				j;
	char			**tmp_color;

	str = NULL;
	tmp_color = NULL;
	if (x == 'F')
		str = data->map->floor_info;
	else if (x == 'C')
		str = data->map->ceiling_info;
	rgb = ft_calloc(3, sizeof(unsigned int));
	i = 0;
	j = 0;
  if (str)
	  tmp_color = ft_split(&str[i], ',');
	if (ft_strslen(tmp_color) > 3)
	{
    data->err_type = E_ERR_VALUES;
		free_strs(tmp_color);
    print_err_and_free(data,rgb);
	}
	while (rgb && tmp_color && tmp_color[j] != NULL)
	{
		check_color_validity(data, tmp_color[j], rgb, tmp_color);
		check_overflow(data, tmp_color[j]);
		rgb[j] = ft_atoi(tmp_color[j]);
		if (rgb[j] > 255)
		{
      data->err_type = E_OUT_OF_RANGE;
      print_err_and_free(data, rgb);
		}
		j++;
	}
	free_strs(tmp_color);
	if (rgb && x == 'F')
		data->map->f_rgb = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	else if (rgb && x == 'C')
		data->map->c_rgb = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
}

void print_err_and_free(t_data *data, void *ptr)
{
  if (data->err_type & E_INV_CHAR)
    ft_putstr_fd(ERR_INVALID_CHAR, 2);
  if (data->err_type & E_MAP_CLOSED)
    ft_putstr_fd(ERR_MAP_NOT_CLOSED, 2);
  if (data->err_type & E_OUT_OF_RANGE)
    ft_putstr_fd(ERR_OUT_OF_RANGE, 2);
  if (data->err_type & E_MISS_INFO)
    ft_putstr_fd(ERR_MISSING_INFO, 2);
  if (data->err_type & E_NO_VAL_SURR)
    ft_putstr_fd(ERR_NO_VALID_SURR, 2);
  if (data->err_type & E_PCOUNT)
    ft_putstr_fd(ERR_PLAYER_COUNT, 2);
  if (data->err_type & E_INV_MAP)
    ft_putstr_fd(ERR_INVALID_MAP, 2);
  if (data->err_type & E_MAL_FAIL)
    ft_putstr_fd(ERR_MALLOC_FAIL, 2);
  if (data->err_type & E_ERR_VALUES)
    ft_putstr_fd(ERR_TOO_MANY_VALUES, 2);
  if (data->err_type & E_OUT_OF_RANGE)
    ft_putstr_fd(ERR_OUT_OF_RANGE, 2);
  if (data->err_type & E_ONLY_DIG)
    ft_putstr_fd(ERR_ONLY_DIGITS, 2);
  free(ptr);
  free_everything(data);
  exit(EXIT_FAILURE);
}

static void	check_overflow(t_data *data, char *str)
{
	int	n;
	int	s;

	n = 0;
	s = 1;
	while (*str >= '0' && *str <= '9')
	{
		n = (n * 10) + (*str - '0');
		if ((n * s) > 255 || (n * s) < 0)
		{
      data->err_type = E_OUT_OF_RANGE;
      print_err_and_free(data,NULL);
		}
		str++;
	}
}

static void	check_color_validity(t_data *data, char *str, unsigned int *rgb,
		char **tmp_color)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(str[i]))
		{
      data->err_type = E_ONLY_DIG;
			free_strs(tmp_color);
      print_err_and_free(data,rgb);
		}
		i++;
	}
}

