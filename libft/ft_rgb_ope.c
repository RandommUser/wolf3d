/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_ope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:10:52 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/10 12:10:55 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	floor(long num)
{
	if (num > 255)
		return (255);
	else if (num < 0)
		return (0);
	else
		return (num);
}

t_rgb		rgb_ope(t_rgb color, char op, double num)
{
	if (op == '/')
	{
		floor(color.red / num);
		floor(color.green / num);
		floor(color.blue / num);
	}
	else if (op == '*')
	{
		floor(color.red * num);
		floor(color.green * num);
		floor(color.blue * num);
	}
	else if (op == '+')
	{
		floor(color.red + num);
		floor(color.green + num);
		floor(color.blue + num);
	}
	else if (op == '-')
	{
		floor(color.red - num);
		floor(color.green - num);
		floor(color.blue - num);
	}
	return (color);
}

t_rgb		rgb_calc(t_rgb color1, t_rgb color2, char type)
{
	if (type == '+')
	{
		floor(color1.red += color2.red);
		floor(color1.green += color2.green);
		floor(color1.blue += color2.blue);
	}
	else if (type == '-')
	{
		floor(color1.red -= color2.red);
		floor(color1.green -= color2.green);
		floor(color1.blue -= color2.blue);
	}
	return (color1);
}
