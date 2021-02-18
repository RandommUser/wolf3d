/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_loops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:08:42 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/12 15:08:43 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	key_press(int key, t_editor *edi)
{
	key_controls(edi->key, KEY_DOWN, key, '+');
	if (key == ESC_KEY)
	{
		map_delete(&edi->map);
		mlx_destroy_image(edi->mlx.mlx_ptr, edi->map_img);
		t_mlx_delete(&edi->mlx);
		good_exit(EXIT_SUCCESS, "Exiting");
	}
	else if (is_pressed(edi->key, KEY_DOWN, L_CTRL) &&
		is_pressed(edi->key, KEY_DOWN, K_S))
	{
		map_save(edi);
		key_controls(edi->key, KEY_DOWN, L_CTRL, '-');
		key_controls(edi->key, KEY_DOWN, K_S, '-');
	}
	else if (is_pressed(edi->key, KEY_DOWN, L_CTRL) &&
		is_pressed(edi->key, KEY_DOWN, K_Z))
	{
		block_undo(&edi->map, NULL, 0, NULL);
		key_controls(edi->key, KEY_DOWN, K_Z, '-');
		block_to_image(edi);
	}
	tool_render(edi->toolbar);
	return (0);
}

int	key_release(int key, t_editor *edi)
{
	return (key_controls(edi->key, KEY_DOWN, key, '-'));
}

int	button_pressed(int button, int x, int y, t_editor *edi)
{
	if (button != MOU_S_D && button != MOU_S_U)
		key_controls(edi->button, MOUSE_DOWN, button, '+');
	edi->mouse_pos = dot(x, y);
	if (button == MOU_L)
		b_block_place(edi, x, y);
	else if (button == MOU_R)
		edi->edit = block_write(edi, x, y);
	else if (button == MOU_S_D)
	{
		edi->zoom *= 1 - EDI_ZOOM_STEP;
		edi->zoom = edi->zoom < EDI_MIN_ZOOM ? EDI_MIN_ZOOM : edi->zoom;
		block_to_image(edi);
	}
	else if (button == MOU_S_U)
	{
		edi->zoom *= 1 + EDI_ZOOM_STEP;
		edi->zoom = edi->zoom > EDI_MAX_ZOOM ? EDI_MAX_ZOOM : edi->zoom;
		block_to_image(edi);
	}
	return (0);
}

int	button_released(int button, int x, int y, t_editor *edi)
{
	x++;
	y++;
	return (key_controls(edi->button, MOUSE_DOWN, button, '-'));
}

int	motion_notify(int x, int y, t_editor *edi)
{
	if (is_pressed(edi->button, MOUSE_DOWN, MOU_M))
	{
		edi->offset.x += ((edi->mouse_pos.x - x) * edi->zoom);
		edi->offset.y += ((edi->mouse_pos.y - y) * edi->zoom);
		edi->offset.x = edi->offset.x < BLOCKW * edi->map.top.x ?
			BLOCKW * edi->map.top.x : edi->offset.x;
		edi->offset.x = edi->offset.x > BLOCKW * edi->map.bottom.x ?
			BLOCKW * edi->map.bottom.x : edi->offset.x;
		edi->offset.y = edi->offset.y < BLOCKW * edi->map.top.y ?
			BLOCKW * edi->map.top.y : edi->offset.y;
		edi->offset.y = edi->offset.y > BLOCKW * edi->map.bottom.y ?
			BLOCKW * edi->map.bottom.y : edi->offset.y;
		edi->mouse_pos.x = x;
		edi->mouse_pos.y = y;
		block_to_image(edi);
	}
	else if (is_pressed(edi->button, MOUSE_DOWN, MOU_L))
		b_block_place(edi, x, y);
	return (0);
}
