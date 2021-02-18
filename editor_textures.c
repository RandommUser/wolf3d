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

/*
** TOOLBAR SELECTED TEXTURE
*/

static void	texs_init(void *mlx_ptr, void **tex, t_box para)
{
	para.i = B_EMPTY + BLOCKSE;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, EMPTY);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
	para.i = B_START + BLOCKSE;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_1, SPAWN_2);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
	para.i = B_END + BLOCKSE;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_2, SPAWN_1);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
	para.i = B_WALL + BLOCKSE;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	wall_color(para.img_dat, para.size, WALL_1, WALL_2);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
	para.i = B_FLOOR + BLOCKSE;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, FLOOR);
	outline_color(para.img_dat, para.size, BAR_SELECTC, -1);
}

/*
** TOOLBAR HOVER TEXTURE
*/

static void	texh_init(void *mlx_ptr, void **tex, t_box para)
{
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, EMPTY);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	para.i = B_START + BLOCKH;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_1, SPAWN_2);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	para.i = B_END + BLOCKH;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_2, SPAWN_1);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	para.i = B_WALL + BLOCKH;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	wall_color(para.img_dat, para.size, WALL_1, WALL_2);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	para.i = B_FLOOR + BLOCKH;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, FLOOR);
	outline_color(para.img_dat, para.size, BAR_HOVERC, -1);
	texs_init(mlx_ptr, tex, para);
}

/*
** EDITOR BLOCK TEXTURE
*/

void		tex_init(void *mlx_ptr, void **tex, int width, int height)
{
	t_box	para;

	para.size = dot(width, height);
	para.i = B_EMPTY;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, EMPTY);
	para.i = B_START;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_1, SPAWN_2);
	para.i = B_END;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	spawn_color(para.img_dat, para.size, SPAWN_2, SPAWN_1);
	para.i = B_WALL;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	wall_color(para.img_dat, para.size, WALL_1, WALL_2);
	para.i = B_FLOOR;
	tex[para.i] = tex_image(mlx_ptr, para);
	para.img_dat = mlx_int_map(tex[para.i], para);
	solid_color(para.img_dat, para.size, FLOOR);
	para.i = B_EMPTY + BLOCKH;
	texh_init(mlx_ptr, tex, para);
}
