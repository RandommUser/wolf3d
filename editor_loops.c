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

int				key(int key, void *param)
{
	t_editor	*edi;

	edi = param;
	if (key == ESC_KEY)
		good_exit(EXIT_SUCCESS, "esc quit");
	else if (key == K_R)
		mlx_clear_window(edi->mlx_ptr, edi->mlx_win);
	else if (key == K_1)
		edi->select = 0;
	else if (key == K_2)
		edi->select = 1;
	else if (key == K_3)
		edi->select = 2;
	else if (key == K_4)
		edi->select = 3;
	return (0);
}

int				mouse(int button, int x, int y, void *param)
{
	t_editor	*edi;
	t_pdot		spot;

	edi = param;
	if (button == MOU_L)
	{
		spot.x = x - BLOCKW / 2 - edi->offset.x;
		spot.y = y - BLOCKW / 2 - edi->offset.y;
		spot.x *= edi->zoom;
		spot.y *= edi->zoom;
		x = spot.x / BLOCKW;
		y = spot.y / BLOCKW;

		//x = x / BLOCKW * BLOCKW * edi->zoom - edi->offset.x;
		//y = y / BLOCKW * BLOCKW * edi->zoom - edi->offset.y;
		mlx_put_image_to_window(edi->mlx_ptr, edi->mlx_win, edi->mlx_img[edi->select], x, y);
	}
	else if (button == MOU_R)
	{
		//x -= BLOCKW / 2;
		//y -= BLOCKW / 2;
		x = x / BLOCKW * BLOCKW * edi->zoom - edi->offset.x;
		y = y / BLOCKW * BLOCKW * edi->zoom - edi->offset.y;
		mlx_put_image_to_window(edi->mlx_ptr, edi->mlx_win, edi->mlx_img[B_FLOOR], x, y);
	}
	else if (button == MOU_S_D)
		edi->select = edi->select == 0 ? BLOCKS + BLOCKSE - 1 : edi->select - 1;
	else if (button == MOU_S_U)
		edi->select = edi->select ==  BLOCKS + BLOCKSE - 1 ? 0 : edi->select + 1;
	printf("B: %d X: %d Y: %d select: %d\n", button, x, y, edi->select);
	return (0);
}


int	key_press(int key, void *para)
{
	t_editor	*edi;

	edi = para;
	if (key == ESC_KEY)
		good_exit(EXIT_SUCCESS, "esc quit");
	if (key_controls(edi->key, KEY_DOWN, key, '+'))
	{
		printf("pressed %d\n", key);
		printf("currently pressed: [%d, %d, %d, %d, %d]\n",
		edi->key[0],edi->key[1],edi->key[2],edi->key[3],edi->key[4]);
	}
	return (0);
}

int key_release(int key, void *para)
{
	t_editor	*edi;

	edi = para;
	key_controls(edi->key, KEY_DOWN, key, '-');
	printf("released %d\n", key);
	printf("currently pressed: [%d, %d, %d, %d, %d]\n", 
	edi->key[0],edi->key[1],edi->key[2],edi->key[3],edi->key[4]);
	return (0);
}

int button_pressed(int button, int x, int y, void *para) // Limit listed buttons?
{
	t_editor	*edi;
	t_pdot		spot;
	t_dot		point;

	edi = para;
	if (button != MOU_S_D && button != MOU_S_U)
		key_controls(edi->button, MOUSE_DOWN, button, '+');
	printf("pressed %d at %d %d\n", button, x, y);
	printf("currently pressed: [%d, %d]\n",
	edi->button[0], edi->button[1]);
	edi->mouse_pos.x = x;
	edi->mouse_pos.y = y;
	if (button == MOU_L)
	{
		spot.x = x - edi->size.x / 2;
		spot.y = y - edi->size.y / 2;
			//printf("stage 1 %f %f\n", spot.x, spot.y);
		spot.x = spot.x * edi->zoom - edi->offset.x;
		spot.y = spot.y * edi->zoom - edi->offset.y;
			//printf("stage 2 %f %f\n", spot.x, spot.y);
		point.x = spot.x / BLOCKW;
		point.y = spot.y / BLOCKW;
		block_edit(edi->start, edi->select, point, NULL);
		//block_list(edi->start);
		printf("block placed at %d %d\n", x ,y);
	}
	else if (button == MOU_R)
	{
		block_to_image(edi);
	}
	return (0);
}

int button_released(int button, int x, int y, void *para)
{
	t_editor	*edi;

	edi = para;
	printf("released %d at %d %d\n", button, x, y);
	key_controls(edi->button, MOUSE_DOWN, button, '-');
	printf("pressed %d at %d %d\n", button, x, y);
	printf("currently pressed: [%d, %d]\n",
	edi->button[0], edi->button[1]);
	return (0);
}

/* any mouse movement, anywhere*/
int	motion_notify(int x, int y, void *para)
{
	t_editor	*edi;
	t_dot		dot;

	edi = para;
	dot.x = x;
	dot.y = y;
	if (is_pressed(edi->button, MOUSE_DOWN, MOU_M))
	{
		//x -= edi->size.x / 2;
		//y -= edi->size.y / 2;
		edi->offset.x -= (edi->mouse_pos.x - x) * edi->zoom;
		edi->offset.y -= (edi->mouse_pos.y - y) * edi->zoom;
		edi->mouse_pos.x = x;
		edi->mouse_pos.y = y;
		//printf("offset %f %f\n", edi->offset.x, edi->offset.y);
		mlx_pixel_put(edi->mlx_ptr, edi->mlx_win, edi->size.x / 2 - edi->offset.x, edi->size.y / 2 - edi->offset.y, 0xff0000);
	}
	//printf("motion at %d %d\n", dot.x, dot.y);
	return (0);
}

int enter_notify(void *para)
{
	t_editor	*edi;

	edi = para;
	printf("enter\n");
	return (0);
}

int leave_notify(void *para)
{
	t_editor	*edi;

	edi = para;
	printf("leave\n");
	return (0);
}
