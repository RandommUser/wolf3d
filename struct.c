/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 12:08:28 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/13 12:08:30 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_dot	dot(int x, int y)
{
	t_dot	this;

	this.x = x;
	this.y = y;
	return (this);
}

t_pdot	pdot(PRECISION x, PRECISION y)
{
	t_pdot	this;

	this.x = x;
	this.y = y;
	return (this);
}

t_nmap	nmap(PRECISION ran11, PRECISION ran12, PRECISION ran21, PRECISION ran22)
{
	t_nmap	ret;

	ret.p = 0;
	ret.ran11 = ran11;
	ret.ran12 = ran12;
	ret.ran21 = ran21;
	ret.ran22 = ran22;
	return (ret);
}
