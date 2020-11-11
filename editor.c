/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 11:42:26 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/11 11:42:27 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		texts_init(void *mlx_ptr, void **text, t_box para)
{
	if (!(text[(para.i = B_START + BLOCKSE)] = mlx_new_image(mlx_ptr,
		para.size.x, para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	spawn_color(para.img_dat, para.size, SPAWN_1, SPAWN_2);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
	if (!(text[(para.i = B_END + BLOCKSE)] = mlx_new_image(mlx_ptr,
		para.size.x, para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	spawn_color(para.img_dat, para.size, SPAWN_2, SPAWN_1);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
	if (!(text[(para.i = B_WALL + BLOCKSE)] = mlx_new_image(mlx_ptr,
		para.size.x, para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	wall_color(para.img_dat, para.size, WALL_1, WALL_2);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
	if (!(text[(para.i = B_FLOOR + BLOCKSE)] = mlx_new_image(mlx_ptr,
		para.size.x, para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	solid_color(para.img_dat, para.size, FLOOR);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
}

static void		texth_init(void *mlx_ptr, void **text, t_box para)
{
	if (!(text[(para.i = B_START + BLOCKH)] = mlx_new_image(mlx_ptr,
		para.size.x, para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	spawn_color(para.img_dat, para.size, SPAWN_1, SPAWN_2);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	if (!(text[(para.i = B_END + BLOCKH)] = mlx_new_image(mlx_ptr,
		para.size.x, para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	spawn_color(para.img_dat, para.size, SPAWN_2, SPAWN_1);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	if (!(text[(para.i = B_WALL + BLOCKH)] = mlx_new_image(mlx_ptr,
		para.size.x, para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	wall_color(para.img_dat, para.size, WALL_1, WALL_2);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	if (!(text[(para.i = B_FLOOR + BLOCKH)] = mlx_new_image(mlx_ptr,
		para.size.x, para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	solid_color(para.img_dat, para.size, FLOOR);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	texts_init(mlx_ptr, text, para);
}

static void		text_init(void *mlx_ptr, void **text, int width, int height)
{
	t_box	para;

	para.size.x = width;
	para.size.y = height;
	if (!(text[(para.i = B_START)] = mlx_new_image(mlx_ptr, para.size.x,
		para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	spawn_color(para.img_dat, para.size, SPAWN_1, SPAWN_2);
	if (!(text[(para.i = B_END)] = mlx_new_image(mlx_ptr, para.size.x,
		para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	spawn_color(para.img_dat, para.size, SPAWN_2, SPAWN_1);
	if (!(text[(para.i = B_WALL)] = mlx_new_image(mlx_ptr, para.size.x,
		para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	wall_color(para.img_dat, para.size, WALL_1, WALL_2);
	if (!(text[(para.i = B_FLOOR)] = mlx_new_image(mlx_ptr, para.size.x,
		para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	solid_color(para.img_dat, para.size, FLOOR);
	texth_init(mlx_ptr, text, para);
}

static t_editor	editor_init(int width, int height, void **img)
{
	t_editor	ret;

	ret.size.x = width;
	ret.size.y = height;
	ret.mlx_img = img;
	ret.name = NULL;
	ret.next = NULL;
	ret.desc = NULL;
	ret.version = NULL;
	ret.offset.x = 0;
	ret.offset.y = 0;
	ret.zoom = 1;
	ret.select = 0;
	ret.port = 1;
	return (ret);
}

int				key(int key, void *param)
{
	t_editor	*edi;

	edi = param;
	if (key == ESC_KEY)
		good_exit(EXIT_SUCCESS, "esc quit");
	else if (key == K_R)
		mlx_clear_window(edi->mlx_ptr, edi->mlx_win);
	else if (key == K_1)
		edi->select = 0;
	else if (key == K_2)
		edi->select = 1;
	else if (key == K_3)
		edi->select = 2;
	else if (key == K_4)
		edi->select = 3;
	return (0);
}

int				mouse(int button, int x, int y, void *param)
{
	t_editor	*edi;

	edi = param;
	if (button == MOU_L)
	{
		//x -= BLOCKW / 2;
		//y -= BLOCKW / 2;
		x = x / BLOCKW * BLOCKW;
		y = y / BLOCKW * BLOCKW;
		mlx_put_image_to_window(edi->mlx_ptr, edi->mlx_win, edi->mlx_img[edi->select], x, y);
	}
	else if (button == MOU_R)
	{
		//x -= BLOCKW / 2;
		//y -= BLOCKW / 2;
		x = x / BLOCKW * BLOCKW;
		y = y / BLOCKW * BLOCKW;
		mlx_put_image_to_window(edi->mlx_ptr, edi->mlx_win, edi->mlx_img[B_FLOOR], x, y);
	}
	else if (button == MOU_S_D)
		edi->select = edi->select == 0 ? BLOCKS + BLOCKSE - 1 : edi->select - 1;
	else if (button == MOU_S_U)
		edi->select = edi->select ==  BLOCKS + BLOCKSE - 1 ? 0 : edi->select + 1;
	printf("B: %d X: %d Y: %d select: %d\n", button, x, y, edi->select);
	return (0);
}

void	editor(void)
{
	void		*mlx_ptr;
	t_editor	editor;
	//t_toolbar	toolbar;
	void		*windows[2];
	void		*textures[EDI_BLOCK * 3];

	if (!(mlx_ptr = mlx_init()))
		err_exit(ERR_MLX, "editor mlx_ptr init failed");
	if (!(windows[0] = mlx_new_window(mlx_ptr, EDI_WIDTH, EDI_HEIGHT, "Map editor")))
		err_exit(ERR_MLX, "editor main window start failed");
	if (!(windows[1] = mlx_new_window(mlx_ptr, BAR_WIDTH, BAR_HEIGHT, "Editor toolbar")))
		err_exit(ERR_MLX, "editor toolbar window start failed");
	editor = editor_init(EDI_WIDTH, EDI_HEIGHT, textures);
	editor.mlx_ptr = mlx_ptr;
	editor.mlx_win = windows[0];
	text_init(mlx_ptr, textures, BLOCKW, BLOCKW);
	mlx_mouse_hook(windows[0], &mouse, &editor);
	mlx_key_hook(windows[0], &key, &editor);
	mlx_loop(mlx_ptr);
}
