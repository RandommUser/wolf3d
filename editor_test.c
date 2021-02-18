/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:52:58 by phakakos          #+#    #+#             */
/*   Updated: 2021/02/18 15:52:59 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	wall(int b)
{
	static int	wall[5] = {1, 2, 3, 4, -1};
	int			i;

	i = -1;
	while (wall[++i] != -1)
		if (wall[i] == b)
			return (1);
	return (0);
}

static int	transparent(int b)
{
	static int	wall[2] = {7, -1};
	int			i;

	i = -1;
	while (wall[++i] != -1)
		if (wall[i] == b)
			return (1);
	return (0);
}

int			is_goal(t_mapb *start, t_dot spot)
{
	t_mapb	*block;

	if (!start)
		return (0);
	block = find_spot(start, spot);
	if (block && block->param && ft_strstr(block->param, MAP_END_FLAG))
		return (1);
	return (0);
}

int			is_transparent(t_mapb *start, t_mapb *block, t_dot spot)
{
	if (!start && !block)
		return (0);
	if (!block)
		block = find_spot(start, spot);
	if (!block)
		return (0);
	if (transparent(block->block))
		return (1);
	return (0);
}

int			is_wall(t_mapb *start, t_mapb *block, t_dot spot)
{
	if (!start && !block)
		return (0);
	if (!block)
		block = find_spot(start, spot);
	if (!block)
		return (0);
	if (wall(block->block))
		return (1);
	return (0);
}
