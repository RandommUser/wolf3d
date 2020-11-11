/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:16:57 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/09 13:18:22 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define PRECISION float

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <pthread.h>
#	include <stdio.h>//

/*
** General definitions
*/

# define THREADS 4

/*
** Key definitions
*/

# define ESC_KEY 53
# define K_R 15
# define K_1 18
# define K_2 19
# define K_3 20
# define K_4 21

/*
** Mouse definitions
*/

# define MOU_L 1
# define MOU_R 2
# define MOU_M 3
# define MOU_S_U 5
# define MOU_S_D 4

/*
** MLX defitions
*/

# define WINDOWS 2
# define MIN_WIDTH 100
# define MIN_HEIGHT 50
# define MAX_WIDTH 2560
# define MAX_HEIGHT 1440

/*
** Game defitions
*/

# define VERSION "0.01"

/*
** Map definitions
*/

# define MAP_VERSION "0.01"
# define MAP_V "V: "MAP_VERSION
# define MAP_NAME "Name: "
# define MAP_DESC "Desc: "
# define MAP_NEXT "Next: "
# define MAP_END "END"
# define MAP_MAX_PORT 64
# define MAP_MIN_X -200
# define MAP_MAX_X 200
# define MAP_MIN_Y -200
# define MAP_MAX_Y 200

/*
** Editor definitions
*/

# define EDI_WIDTH 600
# define EDI_HEIGHT 400
# define EDI_BLOCK 4 			// amount of blocks placeable
# define EDI_BLOCKW 50			// block pixel size
# define EDI_MIN_ZOOM 0.25
# define EDI_MAX_ZOOM 4
# define EDI_ZOOM_STEP 0.1

/*
** Editor toolbar definitions
*/

# define BAR_WIDTH 300
# define BAR_HEIGHT 50
# define BAR_HOVERC 0xfff700
# define BAR_SELECTC 0xff0000


/*
** Editor block definitions
*/

# define BLOCKW EDI_BLOCKW
# define BLOCKS EDI_BLOCK
# define BLOCKH EDI_BLOCK
# define BLOCKSE EDI_BLOCK * 2
# define BLOCK0 0
# define BLOCK1 1
# define BLOCK2 2
# define BLOCK3 3
# define BLOCK4 4
# define BLOCK5 5
# define B_START BLOCK0
# define B_END BLOCK1
# define B_WALL BLOCK2
# define B_FLOOR BLOCK3

/*
** "Texture" color definitions
*/

# define SPAWN_1 0x888888
# define SPAWN_2 0xffffff
# define WALL_1 0x52504d
# define WALL_2 0xdddddd
# define FLOOR 0x333333

/*
** Exit codes
*/

# define USAGE 1
# define ERR_THREAD_VAL 2
# define ERR_MLX 3
# define ERR_MEMORY 4
# define ERR_PARA 5
# define X_EXIT 6//EXIT_SUCCESS


typedef struct		s_dot
{
	int	x;
	int	y;
}					t_dot;

typedef struct		s_pdot
{
	PRECISION	x;
	PRECISION	y;
}					t_pdot;

typedef struct		s_mapb
{
	t_dot	base_s;
	t_dot	top_s;
	char	*block;
	void	*next;
}					t_mapb;

typedef struct		s_editor
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		**mlx_img;
	char		*version;	// map file data // NEEDED?? just use MAP_V
	char		*name;
	char		*desc;
	char		*next;
	t_mapb		*start;	// start point pointer
	int			select;	// selected block
	char		port;	// teleport number
	t_dot		size;
	t_pdot		offset;
	PRECISION	zoom;
}					t_editor;

typedef struct		s_toolbar
{
	void		**mlx_img;
	t_dot		size;
	t_editor	editor;
}					t_toolbar;

typedef struct		s_box
{
	int		*img_dat;
	int		endian;
	int		bpp;
	int		line_size;
	int		i;
	t_dot	size;
}					t_box;

void				good_exit(int code, char *msg);
void				err_exit(int error, char *msg);

void				editor(void);

void				spawn_color(int *text, t_dot size, int color1, int color2);
void				wall_color(int *text, t_dot size, int color1, int color2);
void				outline_color(int *text, t_dot size, int color1, int color2);
void				solid_color(int *text, t_dot size, int color);

#endif
