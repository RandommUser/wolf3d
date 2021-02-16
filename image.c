/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 12:27:09 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/13 12:27:11 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	image_wipe(int *img_dat, int color, int width, int height)
{
	int	i;

	if (!img_dat)
		return ;
	i = -1;
	while (++i < width * height)
		img_dat[i] = color;
}

static void	write_tex(t_box box)
{
	box.img_dat = mlx_int_map(box.edit->mlx_img[box.curr->block], box);
	while (iround(box.texture.y) < BLOCKW && box.image.y + box.prog.y <
		box.edit->size.y)
	{
		box.texture.x = box.tcorr.x;
		box.prog.x = box.pcorr.x;
		while (iround(box.texture.x) < BLOCKW && box.image.x + box.prog.x
			< box.edit->size.x)
		{
			box.edit->map_data[box.prog.x + box.image.x + (box.prog.y +
				box.image.y) * box.edit->size.x] = box.img_dat[
				iround(box.texture.x) + iround(box.texture.y) * BLOCKW];
			box.prog.x++;
			box.texture.x += box.step;
		}
		box.prog.y++;
		box.texture.y += box.step;
	}
}

void	edi_block_image(t_box box)
{
	box.step = 1 * box.edit->zoom;
	box.image.x = iround(pmap(box.spot.x, nmap(box.edit->offset.x - box.w,
		box.edit->offset.x + box.w, 0, box.edit->size.x - 1)));
	box.image.y = iround(pmap(box.spot.y, nmap(box.edit->offset.y - box.h,
		box.edit->offset.y + box.h, 0, box.edit->size.y - 1)));
	box.prog = dot(0, 0);
	box.pcorr = dot(0, 0);
	box.tcorr = pdot(0, 0);
	box.texture = pdot(0, 0);
	if (box.image.x < 0)
	{
		box.pcorr.x = ft_abs(box.image.x);
		box.tcorr.x = box.pcorr.x * box.step;
	}
	if (box.image.y < 0)
	{
		box.prog.y = ft_abs(box.image.y);
		box.texture.y = box.prog.y * box.step;
	}
	write_tex(box);
}
