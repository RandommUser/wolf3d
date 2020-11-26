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
		err_exit(ERR_MEMORY, "block add alloc fail");
	ret->param = NULL;
	if (block->param && !(ret->param = ft_strdup(block->param)))
		err_exit(ERR_MEMORY, "block add alloc fail");
	ret->pos = block->pos;
	ret->block = block->block;
	ret->next = NULL;
	return (ret);
}

static int	block_comp(t_mapb *block1, t_mapb *history, int b, char *param)
{
	if (!history)
		return (1);
	if (block1->block != b)
		return (1);
	if ((block1->param && !param) || (!block1->param && param))
		return (1);
	if (block1->param && param && ft_strcmp(block1->param, param))
		return (1);
	return (0);
}

void		block_undo(t_editor *edit, t_mapb *block, int b, char *param)
{
	static t_mapb	*history[EDI_HISTORY + 1];
	t_mapb			temp;
	int				i;

	i = 0;
//	block_free(history[EDI_HISTORY]);
//	history[EDI_HISTORY] = NULL;
	if (block && block_comp(block, history[i], b, param))
	{
		printf("added\n");
		while (history[i])
			i++;
		if (i == EDI_HISTORY)
			block_free(history[--i]);
		while (i-- > 0)
			history[i + 1] = history[i];
		history[0] = dube_block(block);
	}
	else if (!block)
	{
		if (history[i])
		{
			printf("undo\n");
			temp.block = history[i]->block;
			temp.pos = history[i]->pos;
			temp.param = history[i]->param;
			free(history[i]);
			history[i] = NULL;
			block_edit(edit, temp.block, temp.pos, temp.param);
			block_free(history[i]);
		}
		while (i++ < EDI_HISTORY)
			history[i - 1] = history[i];
		block_to_image(edit); // move elsewhere?
	}
}
