/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:39:40 by phakakos          #+#    #+#             */
/*   Updated: 2021/02/18 15:39:42 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	input_print(t_editor *edit, char *smsg, char *cmsg)
{
	block_to_image(edit);
	write_to_screen(edit->mlx, dot(20, 10), 0x00ff00, smsg);
	mlx_do_sync(edit->mlx.mlx_ptr);
	ft_putstr(cmsg);
}

static void	*input_loop(t_editor *edit, char *smsg, char *cmsg, char *curr)
{
	char	*str;

	input_print(edit, smsg, cmsg);
	if (curr)
	{
		ft_putstr("or press Enter for current '");
		ft_putstr(curr);
		ft_putstr("'\n");
	}
	if (get_next_line(0, &str) != 1)
		err_exit(ERR_MEMORY, "input_loop gnl alloc error");
	if (str[0])
	{
		free(curr);
		return (str);
	}
	free(str);
	if (curr)
		return (curr);
	else
	{
		ft_putstr("Please give an input!!\n");
		return (input_loop(edit, smsg, cmsg, curr));
	}
}

void		map_save(t_editor *edit)
{
	edit->map.name = input_loop(edit, "Write name in console",
		"Write the name\n", edit->map.name);
	ft_putstr("Name is now: ");
	ft_putendl(edit->map.name);
	edit->map.desc = input_loop(edit, "Write description in console",
		"Write the description\n", edit->map.desc);
	ft_putstr("Description is now: ");
	ft_putendl(edit->map.desc);
	if (map_write(&edit->map))
		ft_putstr("Map saved succesfully\n");
	else
		ft_putstr("Failed to open/create the file. "
		"Please check your permissions\n");
	block_to_image(edit);
}

int			editor_exit(t_editor *edit)
{
	tool_exit(edit->toolbar);
	return (0);
}

void		block_free(t_mapb *block)
{
	if (!block)
		return ;
	free(block->param);
	free(block);
	block = NULL;
}
