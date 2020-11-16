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

t_mapb		*find_spot(t_mapb *start, t_dot spot)
{
	t_mapb	*curr;

	if (!start)
		return (NULL);
	curr = start;
	while(curr)
	{
		if (curr->base_s.x == spot.x && curr->base_s.y == spot.y)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

static int block_check(t_mapb *block, char *str)
{
	return (block && block->param && ft_strstr(block->param, str));
}

static void block_param(t_mapb *block, char *param)
{
	if (block->param)
		free(block->param);
	block->param = NULL;
	if (param && !(block->param = ft_strdup(param)))
	{
		free(block);
		err_exit(ERR_MEMORY, "block param alloc fail");
	}
}

static void	block_free(t_mapb *block)
{	// FREE STUFF HERE
	free(block->param);
	free(block);
	block = NULL;
}

int		map_valid(t_editor *edit, t_mapb *start)
{
	t_dot	goals;
	t_mapb	*curr;

	goals = dot(0, 0);
	curr = start;
	while (curr)
	{
		if(block_check(curr, MAP_SPAWN_FLAG))
			if (goals.x++)
			{
				mlx_string_put(edit->mlx_ptr, edit->mlx_win, 20, 10, 0xff0000, "TOO MANY SPAWNS");
				return (0);
			}
		if (block_check(curr, MAP_END_FLAG))
			goals.y++;
		if (curr->base_s.x < -MAP_SIZE / 2 || curr->base_s.x > MAP_SIZE / 2 ||
		curr->base_s.y < -MAP_SIZE / 2 || curr->base_s.y > MAP_SIZE / 2)
		{
			mlx_string_put(edit->mlx_ptr, edit->mlx_win, 20, 10, 0xff0000, "BLOCK OUT OF MAP");
			return (0);
		}
		curr = curr->next;
	}
	if (!goals.x)
		mlx_string_put(edit->mlx_ptr, edit->mlx_win, 20, 10, 0xff0000, "NO START");
	else if (!goals.y)
		mlx_string_put(edit->mlx_ptr, edit->mlx_win, 20, 10, 0xff0000, "NO END");
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
		if (curr->base_s.x == spot.x &&
			curr->base_s.y == spot.y)
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

t_mapb	*block_add(t_mapb *start, int block, t_dot spot, char *param)
{
	t_mapb	*curr;
	t_mapb	*this;

	if (!(this = malloc(sizeof(t_mapb))))
		err_exit(ERR_MEMORY, "block add alloc fail");
	this->param = NULL;
	block_param(this, param);
	this->base_s.x = spot.x;
	this->base_s.y = spot.y;
	this->block = block;
	this->next = NULL;
	if (!start)
		return (this);
	curr = start;
	while (curr->next)
		curr = curr->next;
	curr->next = &this;
	return (this);
}

int		block_edit(t_mapb *start, int block, t_dot spot, char *param)
{
	t_mapb	*curr;

	if (!start)
		return (0);
	curr = start;
	if (spot.x < -MAP_SIZE / 2 || spot.x > MAP_SIZE / 2 ||
		spot.y < -MAP_SIZE / 2 || spot.y > MAP_SIZE / 2)
			return (0);
	while (curr)
	{
		if (curr->base_s.x == spot.x && curr->base_s.y == spot.y)
		{
			if (!block_check(curr, MAP_SPAWN_FLAG))
			{
				curr->block = block;
				block_param(curr, param);
				return (1);
			}
			break ;
		}
		if (!curr->next)
		{
			curr->next = block_add(curr, block, spot, param);
			break ;
		}
		curr = curr->next;
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
		printf("Block #%d\nX: %d Y: %d\nBlock: %d\nParam: %s\nNext: %p\n", i,
		curr->base_s.x, curr->base_s.y, curr->block, curr->param, curr->next);
		curr = curr->next;
	}
}

void	block_to_image(t_editor *edit)
{

	t_box		box;
	t_pdot		spot;
//	t_dot		text;

	if (!(box.curr = edit->start))
		return ;
	image_wipe(edit->map_data, 0x000000, edit->size.x, edit->size.y);
	box.blockw = BLOCKW * edit->zoom;
	box.w = edit->size.x / 2 * edit->zoom;
	box.h = edit->size.y / 2 * edit->zoom;
	box.i = 0;
	while (box.curr)
	{
		//spot.x = box.curr->base_s.x * box.blockw - box.blockw / 2;
		//spot.y = box.curr->base_s.y * box.blockw - box.blockw / 2;
		spot.x = box.curr->base_s.x * BLOCKW - BLOCKW / 2;
		spot.y = box.curr->base_s.y * BLOCKW - BLOCKW / 2;
		if ((spot.x >= edit->offset.x - box.w && spot.x <= edit->offset.x + box.w) ||
		(spot.x + BLOCKW >= edit->offset.x - box.w && spot.x + BLOCKW <= edit->offset.x + box.w))
		{
			if ((spot.y >= edit->offset.y - box.h && spot.y <= edit->offset.y + box.h) ||
			(spot.y + BLOCKW >= edit->offset.y - box.h && spot.y + BLOCKW <= edit->offset.y + box.h))
			{
				box.edit = edit;
				box.spot = spot; // blockw, w, h, spot, edit, curr
				mlx_pixel_put(edit->mlx_ptr, edit->mlx_win, spot.x + edit->size.x / 2 - edit->offset.x, spot.y + edit->size.y / 2 - edit->offset.y, 0xffffff);
				//printf("block #%d in view, X %f Y %f | base %d %d\n", box.i, spot.x, spot.y, box.curr->base_s.x, box.curr->base_s.y);
				edi_block_image(box);
			}
		}
		box.curr = box.curr->next;
		box.i++;
	}
	mlx_clear_window(edit->mlx_ptr, edit->mlx_win);
	mlx_put_image_to_window(edit->mlx_ptr, edit->mlx_win, edit->map_img, 0, 0);
}
