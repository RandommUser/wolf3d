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

int			is_transparent(t_mapb *start, t_dot spot)
{
	t_mapb	*block;

	block = find_spot(start, spot);
	if (!block)
		return (0);
	if (block->block == 7)
		return (1);
	return (0);
}

int			is_wall(t_mapb *start, t_dot spot)
{
	t_mapb	*block;

	block = find_spot(start, spot);
	if (!block)
		return (0);
	if (block->block == 1 || block->block == 2 ||
		block->block == 4 || block->block == 3)
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
	while (curr->next)
		curr = curr->next;
	return (curr);
}

int 		block_check(t_mapb *block, char *str)
{
	return (block && block->param && ft_strstr(block->param, str));
}

static void block_param(t_mapb *block, char *param)
{
	if (block->param)
		free(block->param);
	block->param = param;
	/*
	block->param = NULL;
	if (param && !(block->param = ft_strdup(param)))
	{
		free(block);
		err_exit(ERR_MEMORY, "block param alloc fail");
	}
	*/
}

void	block_free(t_mapb *block)
{	// FREE STUFF HERE
	if (!block)
		return ;
	free(block->param);
	free(block);
	block = NULL;
}

int		map_valid(t_map *map, t_mlx *mlx)
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
				write_to_screen(*mlx, dot(20, 10), 0xff0000, "TOO MANY SPAWNS");
				return (0);
			}
		if (block_check(curr, MAP_END_FLAG))
			goals.y++;
		if ((map->size.x > 0 && (curr->pos.x < -map->size.x || curr->pos.x > map->size.x )) ||
		(map->size.y > 0 && (curr->pos.y < -map->size.y || curr->pos.y > map->size.y)))
		{
			write_to_screen(*mlx, dot(20, 10), 0xff0000, "BLOCK OUT OF MAP");
			return (0);
		}
		curr = curr->next;
	}
	if (!goals.x)
		write_to_screen(*mlx, dot(20, 10), 0xff0000, "NO START");
	else if (!goals.y)
		write_to_screen(*mlx, dot(20, 10), 0xff0000, "NO END");
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

int		block_cut(t_mapb *start, t_dot spot)
{
	t_mapb	*curr;
	t_mapb	*previous;

	curr = start;
	previous = NULL;
	while (curr)
	{
		if (curr->pos.x == spot.x &&
			curr->pos.y == spot.y)
		{
			if (previous)
			{
				block_free(curr);
				previous->next = curr->next;
				return (1);
			}
			else
			{ 
				block_free(curr);
				start = curr->next;
				return (-1);
			}
		}
		previous = curr;
		curr = curr->next;
	}
	return (0);
}

t_mapb	*block_add(t_map *map, int block, t_dot spot, char *param)
{
	t_mapb	*curr;
	t_mapb	*this;

	if ((map->size.x > 0 && (spot.x < -map->size.x || spot.x > map->size.x )) ||
		(map->size.y > 0 && (spot.y < -map->size.y || spot.y > map->size.y)))
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
	/*
	if ((edit->map_size.x > 0 && (spot.x < -edit->map_size.x || spot.x > edit->map_size.x )) ||
		(edit->map_size.y > 0 && (spot.y < -edit->map_size.y || spot.y > edit->map_size.y)))
			return (0);*/
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
		if ((curr->next = block_add(map, block, spot, param)))
			return (1);
	}
	return (0);
}

void	block_list(t_mapb *start)
{
	t_mapb	*curr;
	int		i;

	curr = start;
	i = 0;
	while (curr)
	{
		i++;
		printf("Block #%d\nX: %d Y: %d\n",i,curr->pos.x, curr->pos.y);
		printf("Block: %d\n",curr->block);
		printf("Param: %s\n", curr->param);
		printf("Next: %p\n", curr->next);
		curr = curr->next;
	}
}

void	block_to_image(t_editor *edit)
{

	t_box		box;
	t_pdot		spot;
//	t_dot		text;

	if (!(box.curr = edit->map.start))
		return ;
	image_wipe(edit->map_data, MAP_BASE, edit->size.x, edit->size.y);
	box.blockw = BLOCKW * edit->zoom;
	box.w = edit->size.x / 2 * edit->zoom;
	box.h = edit->size.y / 2 * edit->zoom;
	box.i = 0;
	while (box.curr)
	{
		//spot.x = box.curr->pos.x * box.blockw - box.blockw / 2;
		//spot.y = box.curr->pos.y * box.blockw - box.blockw / 2;
		spot.x = box.curr->pos.x * BLOCKW - BLOCKW / 2;
		spot.y = box.curr->pos.y * BLOCKW - BLOCKW / 2;
		if ((spot.x >= edit->offset.x - box.w && spot.x <= edit->offset.x + box.w) ||
		(spot.x + BLOCKW >= edit->offset.x - box.w && spot.x + BLOCKW <= edit->offset.x + box.w))
		{
			if ((spot.y >= edit->offset.y - box.h && spot.y <= edit->offset.y + box.h) ||
			(spot.y + BLOCKW >= edit->offset.y - box.h && spot.y + BLOCKW <= edit->offset.y + box.h))
			{
				box.edit = edit;
				box.spot = spot; // blockw, w, h, spot, edit, curr
				mlx_pixel_place(edit->mlx, dot(spot.x + edit->size.x / 2 - edit->offset.x,
					spot.y + edit->size.y / 2 - edit->offset.y), 0xffffff);
				//printf("block #%d in view, X %f Y %f | base %d %d\n", box.i, spot.x, spot.y, box.curr->base_s.x, box.curr->base_s.y);
				edi_block_image(box);
			}
		}
		box.curr = box.curr->next;
		box.i++;
	}
	mlx_clear_window(edit->mlx.mlx_ptr, edit->mlx.mlx_win);
	mlx_image_place(edit->mlx, edit->map_img, dot(0, 0));
}
