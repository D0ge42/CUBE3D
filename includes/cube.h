#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
#include <sys/types.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_map
{
	char			**map;
	int				is_map_valid;
	int				map_height;
	char			*no_txt_path;
	char			*so_txt_path;
	char			*we_txt_path;
	char			*ea_txt_path;
	char			*ceiling_info;
	char			*floor_info;
	unsigned int	*f_rgb;
	unsigned int	*c_rgb;
	int				map_width;
}				t_map;

typedef struct s_player
{
	int			pos_x;
	int			pos_y;
	char		facing_dir;
	int			exists;
	double			curr_pos_x;
	double			curr_pos_y;
	double			dir_x;
	double			dir_y;
	double			curr_frame;
	double			prev_frame;

}				t_player;

typedef struct s_camera
{
	double plane_x;
	double plane_y;
} t_camera;

typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*win_ptr;

	void		*img;
	void		*img_ptr;
	void		*img_addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			map_ptr;
	t_map		*map;
	t_player	*player;
	t_camera	*camera;

}				t_data;

// Map related functions

char			**fill_map(t_data *data);
void			is_map_valid(t_data *data);
void			is_map_closed(t_data *data);
int				check_and_set(t_data *data, char c, int x, int y);
int				check_zero_surroundings(char **tab, int x, int y);

// Map utils

int				is_coordinate_valid(char **tab, int x, int y);
int				are_sorroundings_valid(char c);

// General strs utils

char			**ft_strscat(char **map, char *str);
void			print_strs(char **map);
int				ft_strslen(char **strs);
void			free_strs(char **strs);
void			free_everything(t_data *data);

// Ray casting

void setup_ray_casting(t_data *data, t_player *player, t_camera *camera);

// Textures

// Convert

void rgb_converter(t_data *data, char x);
void ft_print_rgb(int *RGB);


// Game Loop
void	game_loop(t_data *data, t_player *player, t_map *map, t_camera *camera);
void	draw_mini_map(t_data *data);
void	draw_background(t_data *data);

#endif
