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

int			mlx_pixel_place(t_mlx mlx, t_dot pos, int color)
{
	if (pos.x > mlx.size.x || pos.y > mlx.size.y)
		return (0);
	mlx_pixel_put(mlx.mlx_ptr, mlx.mlx_win, pos.x, pos.y, color);
	return (1);
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

int			mlx_line_to_image(t_image image, t_dot spos, t_dot epos, int color)
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
