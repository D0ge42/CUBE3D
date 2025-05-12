#include "cube.h"
#include "libft.h"
#include <stdlib.h>

//static int ft_atoi_base(char *color);
static void check_color_validity(t_data *data, char *str, unsigned int *rgb, char **tmp_color);
static void	check_overflow(t_data *data, char *str);

void rgb_converter(t_data *data, char x)
{
  char *str = NULL;
  if (x == 'F')
    str = data->map->floor_info;
  else if (x == 'C')
    str = data->map->ceiling_info;
  if (str == NULL)
  {
    free_everything(data);
    exit(EXIT_FAILURE);
  }
  unsigned int *rgb = ft_calloc(3,sizeof(unsigned int));
  if (rgb == NULL)
  {
    ft_putstr_fd(ERR_MALLOC_FAIL,2);
    free(rgb);
    free_everything(data);
    exit(EXIT_FAILURE);
  }
  int i = 0;
  int j = 0;
  char **tmp_color = ft_split(&str[i],',');
  if (ft_strslen(tmp_color) > 3)
  {
    ft_putstr_fd(ERR_TOO_MANY_VALUES, 2);
    free_strs(tmp_color);
    free(rgb);
    free_everything(data);
    exit(EXIT_FAILURE);
  }
  if (tmp_color == NULL)
  {
    ft_putstr_fd(ERR_MALLOC_FAIL,2);
    free(rgb);
    free_everything(data);
    exit(EXIT_FAILURE);
  }
  while(tmp_color[j] != NULL)
  {
    check_color_validity(data,tmp_color[j],rgb,tmp_color);
    check_overflow(data,tmp_color[j]);
    rgb[j] = ft_atoi(tmp_color[j]);
    if (rgb[j] > 255)
    {
      free_everything(data);
      ft_putstr_fd(ERR_OUT_OF_RANGE,2);
      exit(EXIT_FAILURE);
    }
    j++;
  }
  free_strs(tmp_color);
  if (x == 'F')
    data->map->f_rgb = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
  else if (x == 'C')
    data->map->c_rgb = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
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
    ft_putstr_fd(ERR_OUT_OF_RANGE,2);
    free_everything(data);
    exit(EXIT_FAILURE);
  }
		str++;
	}
}

static void check_color_validity(t_data *data, char *str, unsigned int *rgb, char **tmp_color)
{
  int i = 0;
  while(str[i])
  {
    if (str[i] == '\n')
    {
      i++;
      continue;
    }
    if (!ft_isdigit(str[i]))
    {
      ft_putstr_fd(ERR_ONLY_DIGITS,2);
      free_strs(tmp_color);
      free(rgb);
      free_everything(data);
      exit(EXIT_FAILURE);
    }
    i++;
  }
}

void ft_print_rgb(unsigned int *RGB)
{
  unsigned int i = 0;
  while(i < 3)
  {
    printf("%X\n",RGB[i]);
    i++;
  }
}

