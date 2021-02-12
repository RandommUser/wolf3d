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

t_mapb		*find_spot(t_mapb *start, t_dot spot)
{
	t_mapb	*curr;

	if (!start)
		return (NULL);
	curr = start;
	while(curr)
	{
		if (curr->pos.x == spot.x && curr->pos.y == spot.y)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

static t_mapb	*find_last(t_mapb *start)
{
	t_mapb *curr;

	curr = start;
	while (curr && curr->next)
		curr = curr->next;
	return (curr);
}

int 		block_check(t_mapb *block, char *str)
{
	return (block && block->param && !ft_strcmp(block->param, str));
}

static void block_param(t_mapb *block, char *param)
{
	if (!block)
		return ;
	if (block->param)
		free(block->param);
	block->param = param;
}

void	block_free(t_mapb *block)
{	// FREE STUFF HERE
	if (!block)
		return ;
	free(block->param);
	free(block);
	block = NULL;
}

int		map_valid(t_map *map)
{
	t_dot	goals;
	t_mapb	*curr;

	goals = dot(0, 0);
	curr = map->start;
	while (curr)
	{
		if(block_check(curr, MAP_SPAWN_FLAG))
			if (goals.x++)
			{
				ft_putstr("TOO MANY SPAWNS\n");
				return (0);
			}
		if (block_check(curr, MAP_END_FLAG))
			goals.y++;
		curr = curr->next;
	}
	if (!goals.x)
		ft_putstr("NO START\n");
	else if (!goals.y)
		ft_putstr("NO END\n");
	return (goals.x && goals.y);
}

void	block_tree_del(t_mapb *start)
{
	t_mapb	*curr;
	t_mapb	*next;

	curr = start;
	while (curr)
	{
		next = curr->next;
		block_free(curr);
		curr = next;
	}
}

t_mapb	*block_add(t_map *map, int block, t_dot spot, char *param)
{
	t_mapb	*curr;
	t_mapb	*this;

	if ((map->size.x > 0 && (spot.x < map->top.x || spot.x > map->bottom.x ))
		|| (map->size.y > 0 && (spot.y < map->top.y || spot.y > map->bottom.y))
		)
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

int		block_edit(t_map *map, int block, t_dot spot, char *param)
{
	t_mapb	*curr;

	if (!map || !map->start)
		return (0);
	curr = find_spot(map->start, spot);
	if (curr && !(curr->block == 6 && block_check(curr, MAP_SPAWN_FLAG)))
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

/*
** block_to_image helper
*/

static int		on_screen(t_pdot pos, t_pdot off, t_box box)
{
	if (pos.x < off.x - box.w && pos.x + BLOCKW < off.x - box.w)
		return (0);
	if (pos.x > off.x + box.w && pos.x + BLOCKW > off.x + box.w)
		return (0);
	if (pos.y < off.y - box.h && pos.y + BLOCKW < off.y - box.h)
		return (0);
	if (pos.y > off.y + box.h && pos.y + BLOCKW > off.y + box.h)
		return (0);
	return (1);
}

void	block_to_image(t_editor *edit)
{

	t_box		box;
	t_pdot		spot;

	if (!(box.curr = edit->map.start))
		return ;
	image_wipe(edit->map_data, MAP_BASE, edit->size.x, edit->size.y);
	box.blockw = BLOCKW * edit->zoom;
	box.w = edit->size.x / 2 * edit->zoom;
	box.h = edit->size.y / 2 * edit->zoom;
	box.i = -1;
	while (box.curr && ++box.i < 21749647)
	{
		spot.x = box.curr->pos.x * BLOCKW - BLOCKW / 2;
		spot.y = box.curr->pos.y * BLOCKW - BLOCKW / 2;
		if (on_screen(spot, edit->offset, box))
		{
			box.edit = edit;
			box.spot = spot;
			edi_block_image(box);
		}
		box.curr = box.curr->next;
	}
	mlx_clear_window(edit->mlx.mlx_ptr, edit->mlx.mlx_win);
	mlx_image_place(edit->mlx, edit->map_img, dot(0, 0));
}
