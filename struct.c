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

t_pdot	pdot(t_precision x, t_precision y)
{
	t_pdot	this;

	this.x = x;
	this.y = y;
	return (this);
}

t_nmap	nmap(t_precision ran11, t_precision ran12, t_precision ran21, t_precision ra22)
{
	t_nmap	ret;

	ret.p = 0;
	ret.ran11 = ran11;
	ret.ran12 = ran12;
	ret.ran21 = ran21;
	ret.ran22 = ra22;
	return (ret);
}
