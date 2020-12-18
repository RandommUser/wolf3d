/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:52:11 by phakakos          #+#    #+#             */
/*   Updated: 2020/12/14 15:52:12 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		image_set(t_image image, int color)
{
	t_dot	pos;

	pos.y = -1;
	while (++pos.y < image.size.y)
	{
		pos.x = -1;
		while(++pos.x < image.size.x)
			image.img_data[pos.x + pos.y * image.line] = color;
	}
}

void		t_image_del(t_image *image)
{
	mlx_destroy_image(image->mlx_ptr, image->img_ptr);
	image->img_ptr = NULL;
	image->mlx_ptr = NULL;
	image->img_data = NULL;
	image->bpp = 0;
	image->endian = 0;
	image->line = 0;
	image->size = dot(0, 0);
}

t_image		mlx_image(t_mlx mlx, t_dot size, int def)
{
	t_image	image;

	if (!(image.img_ptr = mlx_new_image(mlx.mlx_ptr, size.x, size. y)))
		err_exit(ERR_MLX, "mlx_image() casting failed");
	if (!(image.img_data = (int*)mlx_get_data_addr(image.img_ptr, &image.bpp, &image.line, &image.endian)))
		err_exit(ERR_MLX, "mlx_image() data fetch failed");
	image.line /= 4;
	image.size = size;
	image_set(image, def);
	return (image);
}

int		mlx_line_to_image(t_image image, t_dot spos, t_dot epos, int color)
{
	int		step;
	t_pdot	d;
	t_pdot	inc;

	d.x = epos.x - spos.x;
	d.y = epos.y - spos.y;
	step = ft_fabs(d.x) > ft_fabs(d.y) ? ft_fabs(d.x) : ft_fabs(d.y);
	if (!step)
		return (0);
	inc.x = d.x / step;
	inc.y = d.y / step;
	d.x = spos.x;
	d.y = spos.y;
	while (--step > 0 && (int)d.x < image.size.x && d.x >= 0 && (int)d.y < image.size.y && d.y >= 0)
	{
		image.img_data[(int)d.x + (int)(d.y) * image.line] = color;//(int)d.x % 2 == 0 ? color : 0xff0000;
		d.x += inc.x;
		d.y += inc.y;
		//if (epos.x == 0 && spos.x == 0)
		//	printf("writing to %d %d = %d\n", (int)d.x, (int)d.y, (int)d.x + (int)(d.y) * image.line);
	}
	//printf("inc %f %f size %d\n", inc.x, inc.y, image.line);
	return (1);
}

int		mlx_pixel_place(t_mlx mlx, t_dot pos, int color)
{
	if (pos.x > mlx.size.x || pos.y > mlx.size.y)
		return (0);
	mlx_pixel_put(mlx.mlx_ptr, mlx.mlx_win, pos.x, pos.y, color);
	return (1);
}

int		mlx_image_place(t_mlx mlx, void *img_ptr, t_dot pos)
{
	if (pos.x > mlx.size.x || pos.y > mlx.size.y || !img_ptr)
		return (0);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.mlx_win, img_ptr, pos.x, pos.y);
	return (1);
}

int		t_mlx_delete(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx->mlx_ptr = NULL;
	mlx->mlx_win = NULL;
	mlx->size = dot(0, 0);
	return (1);
}

t_mlx	mlx_start(void *mlx_ptr, int width, int height, char *title)
{
	t_mlx	mlx;

	if (!(mlx.mlx_win = mlx_new_window(mlx_ptr, width, height, title)))
		err_exit(ERR_MLX, "mlx_start() new window");
	mlx.mlx_ptr = mlx_ptr;
	mlx.size = dot(width, height);
	return (mlx);
}
