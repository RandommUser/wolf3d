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


void	edi_block_image(t_box box)
{
	t_dot	image;
	t_dot	prog;
	t_dot	pcorr;
	t_pdot	texture;
	t_pdot	tcorr;
	int		*text_data;

	box.step = 1 * box.edit->zoom;
	image.x = iround(map(box.spot.x,
		nmap(box.edit->offset.x - box.w, box.edit->offset.x + box.w, 0, box.edit->size.x - 1)));
	image.y = iround(map(box.spot.y,
		nmap(box.edit->offset.y - box.h, box.edit->offset.y + box.h, 0, box.edit->size.y - 1)));
	prog = dot(0, 0);
	pcorr = dot(0, 0);
	tcorr = pdot(0, 0);
	texture = pdot(0, 0);
	if (image.x < 0)
	{
		pcorr.x = ft_abs(image.x);
		tcorr.x = pcorr.x * box.step;
	}
	if (image.y < 0)
	{
		prog.y = ft_abs(image.y);
		texture.y = prog.y * box.step;
	}
	text_data = (int*)mlx_get_data_addr(box.edit->mlx_img[box.curr->block], &box.bpp, &box.line_size, &box.endian);
	while (iround(texture.y) < BLOCKW && image.y + prog.y < box.edit->size.y)
	{
		texture.x = tcorr.x;
		prog.x = pcorr.x;
		while (iround(texture.x) < BLOCKW && image.x + prog.x < box.edit->size.x)
		{
			//printf("text %f %f corr %f %f\nimage %d %d corr %d %d\n", texture.x, texture.y, tcorr.x, tcorr.y, prog.x + image.x, prog.y + image.y, pcorr.x, pcorr.y);
			box.edit->map_data[prog.x + image.x + (prog.y + image.y) * box.edit->size.x] = 
				text_data[iround(texture.x) + iround(texture.y) * BLOCKW];
			prog.x++;
			texture.x += box.step;
		}
		prog.y++;
		texture.y += box.step;
	}
}
