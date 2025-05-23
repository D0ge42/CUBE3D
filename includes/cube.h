#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
#include <sys/types.h>
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080

#define ERR_INVALID_CHAR "Error: Invalid char found\n"
#define ERR_MAP_NOT_CLOSED "Error: Map not closed\n"
#define ERR_MISSING_INFO "Error: Info are missing\n"
#define ERR_NO_VALID_SURR "Error: Player has no valid surroundings\n"
#define ERR_PLAYER_COUNT "Error: Player count is invalid\n"
#define ERR_INVALID_MAP "Error: Invalid map\n"

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
	unsigned int	f_rgb;
	unsigned int	c_rgb;
	int				map_width;
	int				map_start;
}				t_map;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	char			facing_dir;
	int				exists;
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

typedef struct s_ray
{
	double	ray_y;
	double	ray_x;
	double	dist_x;
	double	dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		side;
}				t_ray;

// Map related functions

char			**fill_map(t_data *data);
void			is_map_valid(t_data *data);
void			is_map_closed(t_data *data);
int				check_and_set(t_data *data, char c, int x, int y);
int				check_zero_surroundings(t_data *data, char **tab, int x, int y);
void extract_map_only(t_data *data);
void get_map_infos(t_data *data);
void are_all_info_present(t_data *data);
// Map utils

int				is_coordinate_valid(char **tab, int x, int y);

// General strs utils

char			**ft_strscat(char **map, char *str);
void			print_strs(char **map);
int				ft_strslen(char **strs);
void			free_strs(char **strs);
void			free_everything(t_data *data);

// Ray casting

void	raycasting(t_data *data, t_player *player, t_camera *camera);
void	setup_ray_casting(t_data *data, t_player *player, t_camera *camera);
int		two_point_distance(double x, double y, double x2, double y2);

// Textures

// Convert

void rgb_converter(t_data *data, char x);
void ft_print_rgb(unsigned int *RGB);


// Game Loop
void	game_loop(t_data *data, t_player *player, t_map *map, t_camera *camera);
void	draw_mini_map(t_data *data);
void	draw_background(t_data *data);
void	draw_wall(int x, int y, t_ray *ray, t_data *data);

#endif
