/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:36:33 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/26 12:36:35 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_mapb	*dube_block(t_mapb *block)
{
	t_mapb	*ret;

	if (!(ret = malloc(sizeof(t_mapb))))
		err_exit(ERR_MEMORY, "dube block alloc fail");
	ret->param = NULL;
	if (block->param && !(ret->param = ft_strdup(block->param)))
		err_exit(ERR_MEMORY, "dube block alloc fail");
	ret->pos = block->pos;
	ret->block = block->block;
	ret->next = NULL;
	return (ret);
}

static int		block_comp(t_mapb *block, t_mapb *history, int b, char *param)
{
	if (!history)
		return (1);
	if (block->block != b)
		return (1);
	if ((block->param && !param) || (!block->param && param))
		return (1);
	if (block->param && param && ft_strcmp(block->param, param))
		return (1);
	return (0);
}

static int		last_hist(t_mapb *history[EDI_HISTORY + 1], int i)
{
	while (history[i])
		i++;
	return (i);
}

void			block_undo(t_map *map, t_mapb *block, int b, char *param)
{
	static t_mapb	*history[EDI_HISTORY + 1];
	static int		undo = 0;
	int				i;

	i = 0;
	if (!undo && block && block_comp(block, history[i], b, param))
	{
		i = last_hist(history, i);
		if (i == EDI_HISTORY)
			block_free(history[--i]);
		while (i-- > 0)
			history[i + 1] = history[i];
		history[0] = dube_block(block);
	}
	else if (!block)
	{
		if (history[i] && (undo = 1))
		{
			block_edit(map, history[i]->block, history[i]->pos,
				history[i]->param);
			free(history[i]);
		}
		while (!(undo = 0) && i++ < EDI_HISTORY)
			history[i - 1] = history[i];
	}
}
