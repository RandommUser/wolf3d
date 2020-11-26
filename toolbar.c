/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:24:58 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/24 14:24:59 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*block_name(int block)
{
	static char	block_name[BLOCKS + 1][100] = {
		"EMPTY" ,  "START", "EXIT", "WALL", "FLOOR", "\0"
	};
	return (block_name[block]);
}

static void	tool_select(t_toolbar *bar)
{
	t_dot	spot;
	int		i;

	spot = dot(0, BAR_HEIGHT - BAR_BLOCKW);
	i = 0;
	while (++i < BLOCKS)
	{
		if (bar->editor->select == i)
			mlx_put_image_to_window(bar->mlx_ptr, bar->mlx_win,
				bar->editor->mlx_img[i + BLOCKSE], spot.x, spot.y);
		spot.x += BAR_BLOCKW;
	}
	i = 0;
	if (bar->editor->select == i)
		mlx_put_image_to_window(bar->mlx_ptr, bar->mlx_win,
			bar->editor->mlx_img[i + BLOCKSE], spot.x, spot.y);
}

static void	tool_hover(t_toolbar *bar)
{
	t_dot	spot;
	int		i;

	spot = dot(0, BAR_HEIGHT - BAR_BLOCKW);
	i = 0;
	while (++i < BLOCKS)
	{
		if (bar->hover == i)
			mlx_put_image_to_window(bar->mlx_ptr, bar->mlx_win,
				bar->editor->mlx_img[i + BLOCKH], spot.x, spot.y);
		spot.x += BAR_BLOCKW;
	}
	i = 0;
	if (bar->hover == i)
		mlx_put_image_to_window(bar->mlx_ptr, bar->mlx_win,
			bar->editor->mlx_img[i + BLOCKH], spot.x, spot.y);
	tool_select(bar);
}

void		tool_render(t_toolbar *bar)
{
	t_dot	spot;
	int		i;

	mlx_clear_window(bar->mlx_ptr, bar->mlx_win);
	mlx_string_put(bar->mlx_ptr, bar->mlx_win, 5, 0, BAR_C_GOOD, block_name(bar->editor->select));
	spot = dot(0, BAR_HEIGHT - BAR_BLOCKW);
	i = 0;
	while (++i < BLOCKS)
	{
		mlx_put_image_to_window(bar->mlx_ptr, bar->mlx_win,
			bar->editor->mlx_img[i], spot.x, spot.y);
		spot.x += BAR_BLOCKW;
	}
	i = 0;
	mlx_put_image_to_window(bar->mlx_ptr, bar->mlx_win,
			bar->editor->mlx_img[i], spot.x, spot.y);
	tool_hover(bar);
}

int			tool_exit(t_toolbar *param)
{
	t_toolbar	*bar;

	bar = param;
	mlx_destroy_window(bar->mlx_ptr, bar->mlx_win);
	key_press(ESC_KEY, bar->editor);
	return (0);
}
