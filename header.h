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
# include <fcntl.h> // open
# include <unistd.h> // close
# include <pthread.h>
#	include <stdio.h>// <printf>, fprintf

/*
** General definitions
*/

# define THREADS 4
# define ROUNDING >= 0.5

/*
** Key definitions
*/

# define KEY_DOWN 5
# define NO_KEY -1
# define ESC_KEY 53
# define K_R 15
# define K_S 1
# define K_G 5
# define K_1 18
# define K_2 19
# define K_3 20
# define K_4 21

/*
** Mouse definitions
*/

# define MOUSE_DOWN 2
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
** MLX hook definitions
*/

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5
# define MOTION_NOTIFY 6
# define ENTER_NOTIFY 7
# define LEAVE_NOTIFY 8
# define EXPOSE 12
# define WINDOW_CLOSE 17

/*
** Game defitions
*/

# define VERSION "0.01"

/*
** Map definitions
*/

# define MAP_ENDING ".map"
# define MAP_VERSION "0.01"
# define MAP_V "V: "MAP_VERSION
# define MAP_NAME "Name: "
# define MAP_DESC "Desc: "
# define MAP_NEXT "Next: "
# define MAP_END "END"
# define MAP_EMPTY ' '
# define MAP_SPLIT ':'
# define MAP_SPLIT_END ';'
# define MAP_SPAWN_FLAG "START"
# define MAP_END_FLAG "END"
# define MAP_MAX_PORT 64
# define MAP_SIZE 15 // to both directions
# define MAP_MIN_X -50
# define MAP_MAX_X 50
# define MAP_MIN_Y -50
# define MAP_MAX_Y 50

/*
** Editor definitions
*/

# define EDI_WIDTH 600
# define EDI_HEIGHT 400
# define EDI_BLOCK 4 			// amount of blocks placeable
# define EDI_BLOCKW 20			// block pixel size // NEEDS TO BE EVEN FOR PLACEMENT TO WORK PROPERLY
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


typedef struct		s_dot // checks for too much offset
{
	int	x;
	int	y;
}					t_dot;

typedef struct		s_pdot // checks for too much offset
{
	PRECISION	x;
	PRECISION	y;
}					t_pdot;

typedef struct		s_mapb
{
	t_dot	base_s;
	t_dot	top_s;
	int		block;
	char	*param;
	void	*next;
}					t_mapb;

typedef struct		s_editor
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		**mlx_img;
	void		*map_img;
	int			*map_data;
	char		*version;	// map file data // NEEDED?? just use MAP_V
	char		*name; // map file data pointers
	char		*desc;
	char		*next;
	t_mapb		*start;	// start point pointer
	int			select;	// selected block
	char		port;	// teleport number
	t_dot		map_size;
	t_dot		size; // screen
	t_pdot		offset;
	PRECISION	zoom;
	int			key[KEY_DOWN];
	int			button[MOUSE_DOWN];
	t_dot		mouse_pos;
}					t_editor;

typedef struct		s_toolbar
{
	void		**mlx_img;
	t_dot		size;
	t_editor	editor;
}					t_toolbar;

typedef struct		s_nmap
{
	PRECISION	ran11;
	PRECISION	ran12;
	PRECISION	ran21;
	PRECISION	ran22;
	PRECISION	p;
}					t_nmap;


typedef struct		s_box
{
	int			*img_dat;
	int			endian;
	int			bpp;
	int			line_size;
	int			i;
	t_dot		size;
	t_pdot		spot;
	t_mapb		*curr;
	t_editor	*edit;
	PRECISION	blockw;
	PRECISION	w;
	PRECISION	h;
	PRECISION	step;
}					t_box;

void				good_exit(int code, char *msg);
void				err_exit(int error, char *msg);

void				editor(char *arg);
void				text_init(void *mlx_ptr, void **text, int width, int height);

t_mapb				*block_add(t_editor *edit, int block, t_dot spot, char *param);
int					block_edit(t_editor *edit, int block, t_dot spot, char *param);
void				block_list(t_mapb *start);
int					block_cut(t_mapb *start, t_dot spot);
int 				block_check(t_mapb *block, char *str);
void				block_tree_del(t_mapb *start);
void				block_to_image(t_editor *edit);
int					map_valid(t_editor *edit, t_mapb *start);
t_mapb				*find_spot(t_mapb *start, t_dot spot);


int					map_reader(char *name, t_editor *edit);
int					map_write(t_editor *edit);

void				edi_block_image(t_box box);
void				image_wipe(int *img_dat, int color, int width, int height);

int					key(int key, void *param);
int					mouse(int button, int x, int y, void *param);
int					key_press(int key, void *para);
int 				key_release(int key, void *para);
int 				button_pressed(int button, int x, int y, void *para);
int 				button_released(int button, int x, int y, void *para);
int					motion_notify(int x, int y, void *para);
int 				enter_notify(void *para);
int 				leave_notify(void *para);

int					is_pressed(int *tab, int n, int key);
int					key_controls(int *tab, int n, int key, char ac);

void				spawn_color(int *text, t_dot size, int color1, int color2);
void				wall_color(int *text, t_dot size, int color1, int color2);
void				outline_color(int *text, t_dot size, int color1, int color2);
void				solid_color(int *text, t_dot size, int color);


t_dot				dot(int x, int y);
t_pdot				pdot(PRECISION x, PRECISION y);
t_nmap				nmap(PRECISION ran11, PRECISION ran12, PRECISION ran21, PRECISION ran22);


PRECISION			map(PRECISION p, t_nmap ran);
int					iround(PRECISION in);
#endif
