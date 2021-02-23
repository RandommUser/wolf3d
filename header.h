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

# include "precision.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <time.h>
# include <fcntl.h>
# include <unistd.h>

/*
** Key definitions
*/

# define KEY_DOWN 10
# define NO_KEY -1
# define ESC_KEY 53
# define L_CTRL 256
# define L_SHFT 257
# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2
# define K_P 35
# define K_AU 126
# define K_AR 124
# define K_AD 125
# define K_AL 123
# define K_Z 6
# define K_V 9
# define K_C 8
# define K_ENT 36

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

# define TEXT_WIDTH 10
# define TEXT_HEIGHT 16

/*
** MLX hook definitions
*/

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5
# define MOTION_NOTIFY 6
# define WINDOW_CLOSE 17

/*
** Game defitions
*/

# define VERSION "0.02"
# define GWIDTH 900
# define GHEIGHT 600
# define FRAMECAP 144
# define TURN_RATE 0.03
# define MOVE_SPEED 0.1
# define HEAD_TILT 10
# define FOV 0.66
# define RDIST 10
# define PSIZE 0.3
# define RUNNING 1
# define PAUSED 0
# define START_SCREEN 2
# define MENU_PAUSE 1
# define END_SCREEN 3
# define MSELECTED 0xfff600
# define MNORMAL 0xffffff

/*
** Map definitions
*/

# define MAP_ENDING ".map"
# define MAP_V "V: 0.02"
# define MAP_NAME "Name: "
# define MAP_DESC "Desc: "
# define MAP_NEXT "Next: "
# define MAP_END "END"
# define MAP_EMPTY ' '
# define MAP_SPLIT ':'
# define MAP_PARAM_SPLIT ','
# define MAP_SPLIT_END ';'
# define MAP_PARAMS 2
# define MAP_SPAWN_FLAG "START"
# define MAP_END_FLAG "END"
# define MAP_SIZE 15

/*
** Editor definitions
*/

# define EDI_WIDTH 800
# define EDI_HEIGHT 600
# define EDI_BLOCK 5
# define EDI_BLOCKW 40
# define EDI_MIN_ZOOM 0.25
# define EDI_MAX_ZOOM 4
# define EDI_ZOOM_STEP 0.1
# define EDI_HISTORY 50

/*
** Editor toolbar definitions
*/

# define BAR_BLOCKW EDI_BLOCKW
# define BAR_WIDTH 200
# define BAR_HEIGHT 70
# define BAR_HOVERC 0xfff700
# define BAR_SELECTC 0xff0000
# define BAR_C_GOOD 0x00ff00

/*
** Editor block definitions
*/

# define BLOCKW EDI_BLOCKW
# define BLOCKS EDI_BLOCK
# define BLOCKH EDI_BLOCK
# define BLOCKSE 10
# define BLOCK0 0
# define BLOCK1 1
# define BLOCK2 2
# define BLOCK3 3
# define BLOCK4 4
# define B_EMPTY BLOCK0
# define B_START BLOCK1
# define B_END BLOCK2
# define B_WALL BLOCK3
# define B_FLOOR BLOCK4

/*
** "Texture" color definitions
*/

# define SPAWN_1 0x888888
# define SPAWN_2 0xffffff
# define WALL_1 0xa33903
# define WALL_2 0xc4bdb9
# define FLOOR 0x1c8f18
# define EMPTY 0x4a2505
# define MAP_BASE 0x098785

/*
** Exit codes
*/

# define USAGE 1
# define ERR_MLX 3
# define ERR_MEMORY 4
# define ERR_PARA 5

typedef struct		s_dot
{
	int	x;
	int	y;
}					t_dot;

typedef struct		s_pdot
{
	t_precision	x;
	t_precision	y;
}					t_pdot;

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_dot	size;
}					t_mlx;

typedef struct		s_image
{
	void	*mlx_ptr;
	void	*img_ptr;
	int		*img_data;
	int		endian;
	int		bpp;
	int		line;
	t_dot	size;
}					t_image;

typedef struct		s_mapb
{
	t_dot	pos;
	int		block;
	char	*param;
	void	*next;
}					t_mapb;

typedef	struct		s_map
{
	char		*version;
	char		*path;
	char		*name;
	char		*desc;
	char		*next;
	t_dot		spawn;
	t_mapb		*start;
	t_dot		size;
	t_dot		top;
	t_dot		bottom;
}					t_map;

typedef struct		s_player
{
	t_pdot		pos;
	t_pdot		dir;
	t_pdot		plane;
	t_precision	rot;
	char		collision;
	int			look;
}					t_player;

typedef struct		s_game
{
	t_mlx		mlx;
	t_image		image[2];
	int			*text[4];
	t_map		map;
	int			key[KEY_DOWN];
	t_player	player;
	t_precision	frame;
	char		verbose;
	char		state;
	int			mselect;
	int			menu;
}					t_game;

typedef struct		s_ray
{
	t_game		game;
	int			x;
	int			len;
	int			side;
	int			tside;
	int			hit;
	int			lheight;
	int			color[2];
	t_precision	camera;
	t_precision	wdist;
	t_mapb		*block;
	t_pdot		raydir;
	t_pdot		dist;
	t_pdot		sdist;
	t_dot		map;
	t_dot		step;
	t_dot		draw;
}					t_ray;

typedef struct		s_move
{
	t_pdot		opos;
	t_pdot		move;
	t_pdot		movement;
	t_pdot		tplane;
	t_pdot		tdir;
	t_precision	turn;
	int			view;
}					t_move;

typedef struct		s_editor
{
	t_mlx		mlx;
	void		**mlx_img;
	void		*map_img;
	int			*map_data;
	t_map		map;
	t_mapb		*edit;
	int			select;
	t_dot		size;
	t_pdot		offset;
	t_precision	zoom;
	int			key[KEY_DOWN];
	int			button[MOUSE_DOWN];
	t_dot		mouse_pos;
	void		*toolbar;
}					t_editor;

typedef struct		s_toolbar
{
	t_mlx		mlx;
	int			hover;
	t_editor	*editor;
}					t_toolbar;

typedef struct		s_nmap
{
	t_precision	ran11;
	t_precision	ran12;
	t_precision	ran21;
	t_precision	ran22;
	t_precision	p;
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
	t_precision	blockw;
	t_precision	w;
	t_precision	h;
	t_precision	step;
	t_dot		image;
	t_dot		prog;
	t_dot		pcorr;
	t_pdot		texture;
	t_pdot		tcorr;
}					t_box;

typedef struct		s_print
{
	t_mlx	mlx;
	t_dot	pos;
	int		color;
	char	*str;
}					t_print;

void				good_exit(int code, char *msg);
void				err_exit(int error, char *msg);

void				game(char *name);
int					game_exit(t_game *game);
t_player			player_reset(t_game *game);
void				start_menu(t_game *game);

int					game_loop(t_game *game);
int					game_key_down(int key, t_game *game);
int					game_key_up(int key, t_game *game);

int					player_move(t_game *game);
void				raycast(t_game game);
t_ray				ray_setup(t_game game, t_ray ray);
t_ray				ray_colors(t_ray ray);
void				pause_menu(t_game *game, char action);
void				end_menu(t_game *game, char action);

void				editor(char *arg);
void				tex_init(void *mlx_ptr, void **text, int width, int height);

t_mapb				*block_add(t_map *map, int block, t_dot spot, char *param);
int					block_edit(t_map *map, int block, t_dot spot, char *param);
void				block_free(t_mapb *block);
int					block_check(t_mapb *block, char *str);
void				block_tree_del(t_mapb *start);
void				block_undo(t_map *map, t_mapb *block, int b, char *param);
void				block_to_image(t_editor *edit);
int					map_valid(t_map *map);
t_mapb				*find_spot(t_mapb *start, t_dot spot);
int					is_wall(t_mapb *start, t_mapb *block, t_dot spot);
int					is_transparent(t_mapb *start, t_mapb *block, t_dot spot);
int					is_goal(t_mapb *start, t_dot spot);

int					map_reader(char *name, t_map *map);
int					map_header(char *name, int fd, t_map *map);
int					block_read(int fd, t_map *map);
int					map_write(t_map *map);
void				map_save(t_editor *edit);
void				b_block_place(t_editor *edi, int x, int y);
t_mapb				*block_write(t_editor *edi, int x, int y);

void				edi_block_image(t_box box);
void				image_wipe(int *img_dat, int color, int width, int height);

void				tool_render(t_toolbar *bar);
int					bar_mouse_hover(int x, int y, t_toolbar *bar);
int					bar_mouse_click(int button, int x, int y, t_toolbar *bar);
int					tool_exit(t_toolbar *param);
int					bar_key_press(int key, t_toolbar *bar);

int					key_press(int key, t_editor *edi);
int					key_release(int key, t_editor *edi);
int					button_pressed(int button, int x, int y, t_editor *edi);
int					button_released(int button, int x, int y, t_editor *edi);
int					motion_notify(int x, int y, t_editor *edi);
int					editor_exit(t_editor *edit);

void				log_reset(int *tab, int n, int key);
int					is_pressed(int *tab, int n, int key);
int					key_controls(int *tab, int n, int key, char ac);

void				wall_text(int *text, t_dot size, int color1, int color2);
void				spawn_color(int *text, t_dot size, int color1, int color2);
void				wall_color(int *text, t_dot size, int color1, int color2);
void				outline_color(int *text, t_dot size, int color1,
						int color2);
void				solid_color(int *text, t_dot size, int color);

t_dot				dot(int x, int y);
t_pdot				pdot(t_precision x, t_precision y);
t_nmap				nmap(t_precision ran11, t_precision ran12,
						t_precision ran21, t_precision ran22);

void				map_delete(t_map *map);
t_map				map_empty(void);

int					t_mlx_delete(t_mlx *mlx);
t_mlx				mlx_start(void *mlx_ptr, int width, int height,
						char *title);

void				write_to_screen(t_mlx mlx, t_dot pos, int color,
						char *str);
int					mlx_image_place(t_mlx mlx, void *img_ptr, t_dot pos);
int					mlx_pixel_place(t_mlx mlx, t_dot pos, int color);
void				t_image_del(t_image *image);
t_image				mlx_image(t_mlx mlx, t_dot size, int def);
int					mlx_line_to_image(t_image image, t_dot spos, t_dot epos,
						int color);
void				image_set(t_image image, int color);
void				image_combine(t_image img1, t_image img2, int empty);
int					*mlx_int_map(void *img_ptr, t_box box);

t_precision			pmap(t_precision p, t_nmap ran);
int					iround(t_precision in);
int					dround(t_precision in);
#endif
