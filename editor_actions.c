/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:31:08 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/12 15:31:09 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				block_check(t_mapb *block, char *str)
{
	return (block && block->param && ft_strstr(block->param, str));
}

static t_mapb	*find_last(t_mapb *start)
{
	t_mapb *curr;

	curr = start;
	while (curr && curr->next)
		curr = curr->next;
	return (curr);
}

static void		block_param(t_mapb *block, char *param)
{
	if (!block)
		return ;
	if (block->param)
		free(block->param);
	block->param = param;
}

int				block_edit(t_map *map, int block, t_dot spot, char *param)
{
	t_mapb	*curr;

	if (!map || !map->start)
		return (0);
	curr = find_spot(map->start, spot);
	if (curr)
	{
		block_undo(map, curr, block, param);
		curr->block = block;
		block_param(curr, param);
		return (1);
	}
	else if (!curr)
	{
		curr = find_last(map->start);
		if (curr && (curr->next = block_add(map, block, spot, param)))
			return (1);
	}
	return (0);
}

t_mapb			*block_add(t_map *map, int block, t_dot spot, char *param)
{
	t_mapb	*curr;
	t_mapb	*this;

	if ((map->size.x > 0 && (spot.x < map->top.x || spot.x > map->bottom.x))
		|| (map->size.y > 0 && (spot.y < map->top.y
		|| spot.y > map->bottom.y)))
		return (NULL);
	if (!(this = malloc(sizeof(t_mapb))))
		err_exit(ERR_MEMORY, "block add alloc fail");
	this->param = NULL;
	block_param(this, param);
	this->pos.x = spot.x;
	this->pos.y = spot.y;
	this->block = block;
	this->next = NULL;
	if (!map->start)
		return ((map->start = this));
	curr = map->start;
	while (curr->next)
		curr = curr->next;
	curr->next = &this;
	return (this);
}
