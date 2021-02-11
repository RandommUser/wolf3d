/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:56:42 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/12 15:56:43 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_precision	pmap(t_precision p, t_nmap ran)
{
	ran.p = p;
	ran.p = (ran.p - ran.ran11) / (ran.ran12 - ran.ran11);
	ran.p = (ran.ran22 - ran.ran21) * ran.p + ran.ran21;
	return (ran.p);
}

int			iround(t_precision in)
{
	if (in < 0 && (ft_fabs(in) - ft_abs((int)in) ROUNDING))
		return ((int)(in) + 1);
	else if (in - (int)in ROUNDING)
		return ((int)(in) + 1);
	return ((int)in);
}

int			dround(t_precision in)
{
	if (in < 0 && in != (int)in)
		return (in - 1);
	return ((int)in);
}

int			*mlx_int_map(void *img_ptr, t_box box)
{
	int	*ret;

	ret = (int*)mlx_get_data_addr(img_ptr, &box.bpp, &box.line_size, &box.endian);
	if (!ret)
		err_exit(ERR_MLX, "failed to get img_map");
	return (ret);
}