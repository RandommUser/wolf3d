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

void		image_combine(t_image img1, t_image img2, int empty)
{
	t_dot	i;

	i.y = -1;
	while(++i.y < img1.size.y && i.y < img2.size.y)
	{
		i.x = -1;
		while (++i.x < img1.size.x && i.x < img2.size.x)
			if (img2.img_data[i.x + i.y * img2.line] != empty)
				img1.img_data[i.x + i.y * img1.line] = img2.img_data[i.x +
					i.y * img2.line];
	}
}

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
	if (!(image.img_data = (int*)mlx_get_data_addr(image.img_ptr, &image.bpp,
		&image.line, &image.endian)))
		err_exit(ERR_MLX, "mlx_image() data fetch failed");
	image.line /= 4;
	image.size = size;
	image_set(image, def);
	return (image);
}

static int	pos_check(t_image image, t_dot spos, t_dot epos)
{
	if (spos.x < 0 && epos.x < 0)
		return (0);
	if (spos.y < 0 && epos.y < 0)
		return (0);
	if (spos.x >= image.size.x && epos.x >= image.size.x)
		return (0);
	if (spos.y >= image.size.y && epos.y >= image.size.y)
		return (0);
	return (1);
}

static void	mlx_line_setup(int *step, t_pdot *d, t_pdot *inc, int *diff)
{
	if (d->x < 0)
	{
		*diff = -d->x / inc->x;
		d->x += *diff * inc->x;
		d->y += *diff * inc->y;
		*step -= *diff;
	}
	if (d->y < 0)
	{
		*diff = -d->y / inc->y;
		d->y += *diff * inc->y;
		d->x += *diff * inc->x;
		*step -= *diff;
	}
}

int		mlx_line_to_image(t_image image, t_dot spos, t_dot epos, int color)
{
	int		step;
	t_pdot	d;
	t_pdot	inc;
	int		diff;

	d = pdot(epos.x - spos.x, epos.y - spos.y);
	step = ft_fabs(d.x) > ft_fabs(d.y) ? ft_fabs(d.x) : ft_fabs(d.y);
	if (!step || !pos_check(image, spos, epos))
		return (0);
	inc = pdot(d.x / step, d.y / step);
	d = pdot(spos.x, spos.y);
	mlx_line_setup(&step, &d, &inc, &diff);
	while (--step > 0)
	{
		if ((int)d.x < image.size.x && d.x >= 0 && (int)d.y < image.size.y &&
			d.y >= 0)
			image.img_data[(int)d.x + (int)(d.y) * image.line] = color;
		if ((int)(d.x += inc.x) >= image.size.x || (int)d.x < 0
			|| (int)(d.y += inc.y) >= image.size.y || (int)d.y < 0)
			break ;
	}
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
