/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:03:07 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/12 15:03:09 by phakakos         ###   ########.fr       */
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

void				text_init(void *mlx_ptr, void **text, int width, int height)
{
	t_box	para;

	para.size.x = width;
	para.size.y = height;
	if (!(text[(para.i = B_EMPTY)] = mlx_new_image(mlx_ptr, para.size.x,
		para.size.y)))
		err_exit(ERR_MLX, "texture normal init failed");
	para.img_dat = (int*)mlx_get_data_addr(text[para.i], &para.bpp, &para.line_size,
		&para.endian);
	solid_color(para.img_dat, para.size, 0x111111);
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
