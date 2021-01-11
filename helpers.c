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

PRECISION	pmap(PRECISION p, t_nmap ran)
{
	ran.p = p;
	ran.p = (ran.p - ran.ran11) / (ran.ran12 - ran.ran11);
	ran.p = (ran.ran22 - ran.ran21) * ran.p + ran.ran21;
	return (ran.p);
}

int			iround(PRECISION in)
{
	if (in < 0 && (ft_fabs(in) - ft_abs((int)in) ROUNDING))
		return ((int)(in) + 1);
	else if (in - (int)in ROUNDING)
		return ((int)(in) + 1);
	return ((int)in);
}

int			dround(PRECISION in)
{
	if (in < 0 && in != (int)in)
		return (in - 1);
	return ((int)in);
}