/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:42:17 by phakakos          #+#    #+#             */
/*   Updated: 2021/02/18 15:42:19 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	param_check(char *str)
{
	static char	*valid[MAP_PARAMS + 1] = {
		MAP_SPAWN_FLAG, MAP_END_FLAG, "\0"
	};
	int			i;
	int			s;

	i = -1;
	s = 0;
	while (!s && valid[++i][0])
		if (str == ft_strstr(str, valid[i]))
			s = 1;
	if (s)
	{
		i = ft_strlen(valid[i]);
		if (str[i] == MAP_PARAM_SPLIT)
			return (param_check(&str[++i]));
		else if (str[i] == '\0')
			return (1);
	}
	return (0);
}

static void	insert_param(t_editor *edit, t_mapb *block, char *param)
{
	if (!param)
	{
		if (block->block > EDI_BLOCK)
			block->block = block->block % EDI_BLOCK;
		block_edit(&edit->map, block->block, block->pos, param);
	}
	else if (param_check(param))
	{
		if (ft_strstr(param, MAP_SPAWN_FLAG))
			block->block = BLOCKH + B_START;
		else if (ft_strstr(param, MAP_END_FLAG))
			block->block = BLOCKSE + B_END;
		block_edit(&edit->map, block->block, block->pos, param);
	}
	else
	{
		ft_putstr("invalid param!!\n");
		free(param);
	}
	block_to_image(edit);
}

static void	edit_param(t_editor *edit, t_mapb *block)
{
	char	*param;

	write_to_screen(edit->mlx, dot(20, 10), 0x00ff00,
		"Write selected block's param in console");
	mlx_do_sync(edit->mlx.mlx_ptr);
	if (block->param)
	{
		ft_putstr("Press enter for current (");
		ft_putstr(block->param);
		ft_putstr(")\n");
	}
	if (get_next_line(0, &param) != 1)
		err_exit(ERR_MEMORY, "edit_param gnl error");
	if (!param[0])
	{
		free(param);
		if (!(param = ft_strdup(block->param)))
			err_exit(ERR_MEMORY, "edit_param dup err\n");
	}
	else if (!ft_strcmp(param, "NULL"))
	{
		free(param);
		param = NULL;
	}
	insert_param(edit, block, param);
}

t_mapb		*block_write(t_editor *edi, int x, int y)
{
	t_dot		point;
	t_pdot		blocks;
	t_pdot		spot;
	t_mapb		*block;

	spot.x = x - edi->size.x / 2;
	spot.y = y - edi->size.y / 2;
	spot.x = spot.x * edi->zoom + edi->offset.x;
	spot.y = spot.y * edi->zoom + edi->offset.y;
	blocks.x = spot.x / (BLOCKW / 2);
	blocks.y = spot.y / (BLOCKW / 2);
	point.x = (int)(blocks.x) / 2;
	point.x += (int)(blocks.x) % 2;
	point.y = (int)(blocks.y) / 2;
	point.y += (int)(blocks.y) % 2;
	block = find_spot(edi->map.start, point);
	if (edi->edit == block)
	{
		edit_param(edi, block);
		return (NULL);
	}
	return (block);
}

void		b_block_place(t_editor *edi, int x, int y)
{
	t_dot		point;
	t_pdot		blocks;
	t_pdot		spot;

	spot.x = x - edi->size.x / 2;
	spot.y = y - edi->size.y / 2;
	spot.x = spot.x * edi->zoom + edi->offset.x;
	spot.y = spot.y * edi->zoom + edi->offset.y;
	blocks.x = spot.x / (BLOCKW / 2);
	blocks.y = spot.y / (BLOCKW / 2);
	point.x = (int)(blocks.x) / 2;
	point.x += (int)(blocks.x) % 2;
	point.y = (int)(blocks.y) / 2;
	point.y += (int)(blocks.y) % 2;
	block_edit(&edi->map, edi->select, point, NULL);
	block_to_image(edi);
}
