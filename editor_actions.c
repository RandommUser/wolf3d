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
	t_mapb		*curr;
	PRECISION	blockw;
	PRECISION	w;
	PRECISION	h;
	t_pdot		spot;
//	t_dot		text;
	int			i;

	if (!(curr = edit->start))
		return ;
	blockw = BLOCKW * edit->zoom;
	w = edit->size.x / 2 * edit->zoom;
	h = edit->size.y / 2 * edit->zoom;
	i = 0;
	while (curr)
	{
		spot.x = curr->base_s.x * blockw + BLOCKW / 2;
		spot.y = curr->base_s.y * blockw + BLOCKW / 2;
		if (spot.x >= edit->offset.x - w && spot.x <= edit->offset.x + w)
		{
			if (spot.y >= edit->offset.y - h && spot.y <= edit->offset.y + h)
			{
				mlx_pixel_put(edit->mlx_ptr, edit->mlx_win, spot.x + edit->size.x / 2 - edit->offset.x, spot.y + edit->size.y / 2 - edit->offset.y, 0xffffff);
				printf("block #%d in view, X %f Y %f | base %d %d\n", i, spot.x, spot.y, curr->base_s.x, curr->base_s.y);
			}
		}
		curr = curr->next;
		i++;
	}
}
