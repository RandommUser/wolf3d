/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:13:41 by phakakos          #+#    #+#             */
/*   Updated: 2021/02/18 12:13:42 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		mlx_image_place(t_mlx mlx, void *img_ptr, t_dot pos)
{
	if (pos.x > mlx.size.x || pos.y > mlx.size.y || !img_ptr)
		return (0);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.mlx_win, img_ptr, pos.x, pos.y);
	return (1);
}

void	image_combine(t_image img1, t_image img2, int empty)
{
	t_dot	i;

	i.y = -1;
	while (++i.y < img1.size.y && i.y < img2.size.y)
	{
		i.x = -1;
		while (++i.x < img1.size.x && i.x < img2.size.x)
			if (img2.img_data[i.x + i.y * img2.line] != empty)
				img1.img_data[i.x + i.y * img1.line] = img2.img_data[i.x +
					i.y * img2.line];
	}
}

void	image_set(t_image image, int color)
{
	t_dot	pos;

	pos.y = -1;
	while (++pos.y < image.size.y)
	{
		pos.x = -1;
		while (++pos.x < image.size.x)
			image.img_data[pos.x + pos.y * image.line] = color;
	}
}

void	t_image_del(t_image *image)
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

t_image	mlx_image(t_mlx mlx, t_dot size, int def)
{
	t_image	image;

	if (!(image.img_ptr = mlx_new_image(mlx.mlx_ptr, size.x, size.y)))
		err_exit(ERR_MLX, "mlx_image() casting failed");
	if (!(image.img_data = (int*)mlx_get_data_addr(image.img_ptr, &image.bpp,
		&image.line, &image.endian)))
		err_exit(ERR_MLX, "mlx_image() data fetch failed");
	image.line /= 4;
	image.size = size;
	image_set(image, def);
	return (image);
}
