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

static void	*tex_image(void *mlx_ptr, t_box para)
{
	void	*ret;

	ret = mlx_new_image(mlx_ptr, para.size.x, para.size.y);
	if (!ret)
		err_exit(ERR_MLX, "texture init failed");
	return (ret);
}

static void	texs_init(void *mlx_ptr, void **tex, t_box para) // SELECTED
{
	tex[(para.i = B_EMPTY + BLOCKSE)] = tex_image(mlx_ptr, para); // empty
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, EMPTY);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
	tex[(para.i = B_START + BLOCKSE)] = tex_image(mlx_ptr, para); // spawn
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_1, SPAWN_2);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
	tex[(para.i = B_END + BLOCKSE)] = tex_image(mlx_ptr, para); // exit
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_2, SPAWN_1);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
	tex[(para.i = B_WALL + BLOCKSE)] = tex_image(mlx_ptr, para);  // wall
	para.img_dat = mlx_int_map(tex[para.i], para);
	wall_color(para.img_dat, para.size, WALL_1, WALL_2);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
	tex[(para.i = B_FLOOR + BLOCKSE)] = tex_image(mlx_ptr, para); // floor
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, FLOOR);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
}

static void	texh_init(void *mlx_ptr, void **tex, t_box para) // HOVER
{
	tex[(para.i = B_EMPTY + BLOCKH)] = tex_image(mlx_ptr, para);// empty
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, EMPTY);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	tex[(para.i = B_START + BLOCKH)] = tex_image(mlx_ptr, para); // spawn
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_1, SPAWN_2);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	tex[(para.i = B_END + BLOCKH)] = tex_image(mlx_ptr, para); // exit
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_2, SPAWN_1);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	tex[(para.i = B_WALL + BLOCKH)] = tex_image(mlx_ptr, para); // wall
	para.img_dat = mlx_int_map(tex[para.i], para);
	wall_color(para.img_dat, para.size, WALL_1, WALL_2);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	tex[(para.i = B_FLOOR + BLOCKH)] = tex_image(mlx_ptr, para); // floor
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, FLOOR);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	texs_init(mlx_ptr, tex, para);
}

void			tex_init(void *mlx_ptr, void **tex, int width, int height)
{
	t_box	para;

	para.size.x = width;
	para.size.y = height;
	tex[(para.i = B_EMPTY)] = tex_image(mlx_ptr, para); // empty
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, EMPTY);
	tex[(para.i = B_START)] = tex_image(mlx_ptr, para); // spawn
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_1, SPAWN_2);
	tex[(para.i = B_END)] = tex_image(mlx_ptr, para); // exit
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_2, SPAWN_1);
	tex[(para.i = B_WALL)] = tex_image(mlx_ptr, para); // wall
	para.img_dat = mlx_int_map(tex[para.i], para);
	wall_color(para.img_dat, para.size, WALL_1, WALL_2);
	tex[(para.i = B_FLOOR)] = tex_image(mlx_ptr, para); // floor
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, FLOOR);
	texh_init(mlx_ptr, tex, para);
}
