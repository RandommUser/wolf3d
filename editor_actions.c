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

static void	block_free(t_mapb *block)
{	// FREE STUFF HERE
	free(block->param);
	free(block);
	block = NULL;
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
	this->base_s.x = spot.x;
	this->base_s.y = spot.y;
	this->block = block;
	this->param = param;
	this->next = NULL;
	if (!start)
		return (this);
	curr = start;
	while (curr->next)
		curr = curr->next;
	curr->next = &this;
	return (this);
}

void	block_edit(t_mapb *start, int block, t_dot spot, char *param)
{
	t_mapb	*curr;

	if (!start)
		return ;
	curr = start;
	while (curr)
	{
		if (curr->base_s.x == spot.x && curr->base_s.y == spot.y)
		{
			curr->block = block;
			curr->param = param;
			return ;
		}
		if (!curr->next)
		{
			curr->next = block_add(curr, block, spot, param);
			break ;
		}
		curr = curr->next;
	}

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
