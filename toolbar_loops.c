/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbar_loops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:44:28 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/24 16:44:29 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	block_select(int x, int y)
{
	int i;

	if (y < BAR_HEIGHT - BAR_BLOCKW || y > BAR_HEIGHT || x < 0 || x > BAR_WIDTH)
		return (-1);
	i = 0;
	while (++i < BLOCKS)
	{
		if (x >= BAR_BLOCKW * (i - 1) && x <= BAR_BLOCKW * i)
			return (i);
	}
	if (x >= BAR_BLOCKW * (i - 1) && x <= BAR_BLOCKW * i)
			return (0);
	return (-1);
}

int			bar_mouse_hover(int x, int y, void *param)
{
	t_toolbar	*bar;

	bar = param;
	//printf("motion at %d %d\n", x, y);
	if (y < 0 || y > BAR_HEIGHT || x < 0 || x > BAR_WIDTH)
		return ((bar->hover = -1));
	bar->hover = block_select(x, y);
	tool_render(bar);
	return (0);
}

int			bar_mouse_click(int button, int x, int y, void *param)
{
	t_toolbar	*bar;

	bar = param;
	if (y < 0 || y > BAR_HEIGHT || x < 0 || x > BAR_WIDTH)
		return (0);
	if (button == MOU_R)
	{
		bar->editor->select = block_select(x, y) != -1 ? block_select(x, y) : bar->editor->select;
	}
	tool_render(bar);
	return (0);
}
