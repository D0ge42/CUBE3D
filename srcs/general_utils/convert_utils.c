#include "cube.h"
#include <stdlib.h>

//static int ft_atoi_base(char *color);

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
  int i = 0;
  int j = 0;
  while(str[i] && !ft_isdigit(str[i]))
    i++;
  char **tmp_color = ft_split(&str[i],',');
  while(tmp_color[j] != NULL)
  {
    rgb[j] = ft_atoi(tmp_color[j]);
    j++;
  }
  free_strs(tmp_color);
  if (x == 'F')
    data->map->f_rgb = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
  else if (x == 'C')
    data->map->c_rgb = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
}

/*int	get_nb(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
      i++;
	return (i);
}

static int ft_atoi_base(char *color)
{
  int i = 0;
  int res = 0;
  char *base = "0123456789ABCDEF";
  while(color[i])
  {
    res = (res * 16) + (get_nb(color[i],base));
    i++;
  }
  return res;
}*/

void ft_print_rgb(unsigned int *RGB)
{
  unsigned int i = 0;
  while(i < 3)
  {
    printf("%X\n",RGB[i]);
    i++;
  }
}

