/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_coloring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:02:57 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/11 12:02:59 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** color1 = highlight, color2 = base
*/

void	spawn_color(int *text, t_dot size, int color1, int color2)
{
	t_dot	spot;

	if (!text)
		return ;
	spot.y = -1;
	while (++spot.y < size.y)
	{
		spot.x = -1;
		while (++spot.x < size.x)
		{
			text[spot.x + spot.y * size.y] = color2 != -1 ? color2 :
				text[spot.x + spot.y * size.y];
			if ((spot.x > 1 && spot.x < 4 && spot.y > 1 && spot.y < size.y - 2)
			|| (spot.x > 1 && spot.x < size.x - 2 && spot.y > 1 && spot.y < 4)
			|| (spot.x > size.x - 4 && spot.x < size.x - 2 && spot.y > 1 &&
			spot.y < size.y - 2) || (spot.x > 1 && spot.x < size.x - 2 &&
			spot.y > size.y - 4 && spot.y < size.y - 2))
				text[spot.x + spot.y * size.y] = color1;
		}
	}
}

void	wall_color(int *text, t_dot size, int color1, int color2)
{
	t_dot	spot;
	t_dot	t;

	if (!text)
		return ;
	spot.y = -1;
	while (++spot.y < size.y)
	{
		spot.x = -1;
		t.y = !(spot.y % 3) ? 1 : 0;
		while (++spot.x < size.x)
		{
			text[spot.x + spot.y * size.y] = color2 != -1 ? color2 :
				text[spot.x + spot.y * size.y];
			t.x = !(spot.x % 3) ? 1 : 0;
			if ((t.x && t.y) || (!t.x && !t.y))
				text[spot.x + spot.y * size.y] = color1;
		}
	}
}

void	solid_color(int *text, t_dot size, int color)
{
	t_dot	spot;

	if (!text)
		return ;
	spot.y = -1;
	while (++spot.y < size.y)
	{
		spot.x = -1;
		while (++spot.x < size.x)
			text[spot.x + spot.y * size.y] = color;
	}
}

void	outline_color(int *text, t_dot size, int color1, int color2)
{
	t_dot	spot;

	if (!text)
		return ;
	spot.y = -1;
	while (++spot.y < size.y)
	{
		spot.x = -1;
		while (++spot.x < size.x)
		{
			text[spot.x + spot.y * size.y] = color2 != -1 ? color2 :
				text[spot.x + spot.y * size.y];
			if ((spot.y == 0 || spot.y == size.y - 1) ||
				(spot.x == 0 || spot.x == size.x - 1))
				text[spot.x + spot.y * size.y] = color1;
		}
	}
}