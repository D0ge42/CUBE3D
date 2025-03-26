#ifndef CUBE_H
#define CUBE_H

# include "../libft/libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

#define WIDTH 1920
#define HEIGHT 1080

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

}	t_data;

#endif
