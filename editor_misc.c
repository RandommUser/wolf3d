/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_misc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:54:42 by phakakos          #+#    #+#             */
/*   Updated: 2021/02/18 15:54:42 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_mapb		*find_spot(t_mapb *start, t_dot spot)
{
	t_mapb	*curr;

	if (!start)
		return (NULL);
	curr = start;
	while (curr)
	{
		if (curr->pos.x == spot.x && curr->pos.y == spot.y)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void		block_tree_del(t_mapb *start)
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

int			map_valid(t_map *map)
{
	t_dot	goals;
	t_mapb	*curr;

	goals = dot(0, 0);
	curr = map->start;
	while (curr)
	{
		if (block_check(curr, MAP_SPAWN_FLAG) && !is_wall(0, curr, dot(0, 0)))
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

static int	on_screen(t_pdot pos, t_pdot off, t_box box)
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

void		block_to_image(t_editor *edit)
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
