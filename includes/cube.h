#ifndef CUBE_H
#define CUBE_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

#define WIDTH 1920
#define HEIGHT 1080

typedef struct s_map
{

	char **map;
	int is_map_valid;

}	t_map;

typedef struct s_player
{

	int pos_x;
	int pos_y;
	char facing_dir;
	int exists;

}	t_player;

typedef struct s_mlx_data
{
	void *mlx_ptr;
	void *win_ptr;

	void *img;
	void *img_ptr;
	void *img_addr;
	int  bits_per_pixel;
	int  line_length;
	int  endian;
	int map_ptr;
	t_map *map;
	t_player *player;

}	t_data;

// Map related functions

char **fill_map(t_data *data);
void free_strs(char **strs);
int ft_strslen(char **strs);
char **ft_strscat(char **map, char *str);
void print_map(char **map);
int is_valid_char(char c);
void detect_player(t_data *data,char c, int x , int y);
int set_map_struct(t_data *data);

#endif
