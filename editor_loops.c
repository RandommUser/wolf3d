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

static void		*input_loop(t_editor *edit, char *smsg, char *cmsg, char *curr)
{
	char	*str;

	block_to_image(edit);
	mlx_string_put(edit->mlx_ptr, edit->mlx_win, 20, 10, 0x00ff00, smsg);
	mlx_do_sync(edit->mlx_ptr);
	ft_putstr(cmsg);
	if (curr) // has old value
	{
		ft_putstr("or press Enter for current (");
		ft_putstr(curr);
		ft_putstr(")\n");
	}
	if (get_next_line(0, &str) != 1)
		err_exit(ERR_MEMORY, "input_loop gnl alloc error");
	if (str[0]) // good input
		return (str);
	else if (curr && !str[0]) // has already a value, new input empty
	{
		free(str);
		return (curr);
	}
	else // (!curr && !str[0]) // no value, no input
	{
		free(str);
		ft_putstr("Please give an input!!\n");
		return (input_loop(edit, smsg, cmsg, curr));
	}
}

static void		map_save(t_editor *edit)
{
	edit->name = input_loop(edit, "Write name in console", "Write the name\n", edit->name);
	printf("current name> '%s'\n", edit->name);
	edit->desc = input_loop(edit, "Write description in console", "Write the description\n", edit->desc);
	printf("current desc> '%s'\n", edit->desc);
	if (map_valid(edit, edit->start))
	{
		if (map_write(edit))
			printf("map printed\n");
		else
			printf("Map printing failed\n");
	}
	else
		printf("not valid map!\n");
	block_to_image(edit);
}


static int	param_check(char *str)
{
	static char	params[MAP_PARAMS + 1][100] = {
		"START" ,  "END", "\0"
	};
	int	i;
	int	s;
	//params[MAP_PARAMS][0] = '\0';
	i = -1;
	s = 0;
	while (!s && params[++i][0])
		if (str == ft_strstr(str, params[i]))
			s = 1;
	if (s)
	{
		i = ft_strlen(params[i]);
		if (str[i] == MAP_PARAM_SPLIT)
			return (param_check(&str[++i]));
		else if (str[i] == '\0')
			return (1);
	}
	return (0);
}

static	void	edit_param(t_editor *edit, t_mapb *block)
{
	char	*param;

	mlx_string_put(edit->mlx_ptr, edit->mlx_win, 20, 10, 0x00ff00, "Write selected block's param in console");
	mlx_do_sync(edit->mlx_ptr);
	if (block->param) // has old value
	{
		ft_putstr("Press enter for current (");
		ft_putstr(block->param);
		ft_putstr(")\n");
	}
	if (get_next_line(0, &param) != 1)
		err_exit(ERR_MEMORY, "edit_param gnl alloc error");
	else if (!param[0]) // new input empty
	{
		free(param);
		param = ft_strdup(block->param); // alloc check
	}
	else if (!ft_strcmp(param, "NULL")) // input is NULL
	{
		free(param);
		param = NULL;
	}
	if (!param || param_check(param))
	{
		if (block->param)
			free(block->param);
		block->param = param;
	}
	else
	{
		printf("invalid param!!\n");
	}
	block_to_image(edit);
}

static t_mapb	*block_read(t_editor *edi, int x, int y)
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
	block = find_spot(edi->start, point);
	if (edi->edit == block)
	{
		edit_param(edi, block);
		return (NULL);
	}
	else if (block)
	{
		printf("Block X: %d Y: %d\n", block->pos.x, block->pos.y);
		printf("Block: %d\n",block->block);
		printf("Param: %s\n", block->param);
		printf("Next: %p\n", block->next);
	}
	return (block);
}

static void		b_block_place(t_editor *edi, int x, int y)
{
	t_dot		point;
	t_pdot		blocks;
	t_pdot		spot;

	spot.x = x - edi->size.x / 2;
	spot.y = y - edi->size.y / 2;
		//printf("stage 1 %f %f\n", spot.x, spot.y);
	spot.x = spot.x * edi->zoom + edi->offset.x;
	spot.y = spot.y * edi->zoom + edi->offset.y;
		//printf("stage 2 %f %f\n", spot.x, spot.y);
	blocks.x = spot.x / (BLOCKW / 2);
	blocks.y = spot.y / (BLOCKW / 2);
//	printf("spot.x %f / %f | spot.y %f / %f\n", spot.x, (float)(BLOCKW / 2), spot.y, (float)(BLOCKW / 2));
	point.x = (int)(blocks.x) / 2;
	point.x += (int)(blocks.x) % 2;
	point.y = (int)(blocks.y) / 2;
	point.y += (int)(blocks.y) % 2;
//	printf("half-blocks %f %f | rounded %d %d\nfinal %d %d\n", blocks.x, blocks.y, (int)(blocks.x), (int)(blocks.y),
//	point.x, point.y);
	if (block_edit(edi, edi->select, point, NULL))
		printf("block placed at %d %d\n", point.x ,point.y);
	block_to_image(edi);
}

int				key(int key, void *param) // NOT IN USE
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
	else if (key == K_E)
		edi->select = B_EMPTY;
	return (0);
}

int				mouse(int button, int x, int y, void *param) // NOT IN USE
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
	if (key_controls(edi->key, KEY_DOWN, key, '+'))
	{
		printf("pressed %d\n", key);
		printf("currently pressed: [%d, %d, %d, %d, %d]\n",
		edi->key[0],edi->key[1],edi->key[2],edi->key[3],edi->key[4]);
	}
	if (key == ESC_KEY)
	{
		block_tree_del(edi->start);
		free(edi->name);
		free(edi->desc);
		mlx_destroy_image(edi->mlx_ptr, edi->map_img);
		mlx_destroy_window(edi->mlx_ptr, edi->mlx_win);
		good_exit(EXIT_SUCCESS, "esc quit");
	}
	else if (is_pressed(edi->key, KEY_DOWN, L_CTRL) && is_pressed(edi->key, KEY_DOWN, K_S))
		map_save(edi);
	else if (is_pressed(edi->key, KEY_DOWN, L_CMND) && is_pressed(edi->key, KEY_DOWN, K_Z))
	{
		printf("cmnd + z\n");
		block_undo(edi, NULL, 0, NULL);
	}
	else if (key == K_R)
		mlx_clear_window(edi->mlx_ptr, edi->mlx_win);
	else if (key == K_1)
		edi->select = BLOCK1;
	else if (key == K_2)
		edi->select = BLOCK2;
	else if (key == K_3)
		edi->select = BLOCK3;
	else if (key == K_4)
		edi->select = BLOCK4;
	else if (key == K_E)
		edi->select = B_EMPTY;
	//else if (key == K_S)
	//{
	//	map_valid(edi, edi->start);
	//}
	else if (key == K_G)
	{
		map_save(edi);
	}
	tool_render(edi->toolbar);
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

	edi = para;
	if (button != MOU_S_D && button != MOU_S_U)
		key_controls(edi->button, MOUSE_DOWN, button, '+');
	printf("pressed %d at %d %d\n", button, x, y);
	printf("currently pressed: [%d, %d]\n",
	edi->button[0], edi->button[1]);
	edi->mouse_pos.x = x;
	edi->mouse_pos.y = y;
	if (button == MOU_L)
		b_block_place(edi, x, y);
	else if (button == MOU_R)
	{
		//block_to_image(edi);
		/*edi->edit = */block_read(edi, x, y);
		mlx_clear_window(edi->mlx_ptr, edi->mlx_win);
		write_to_editor(edi, dot(x, y), 0xffffff, "this is to test the word-wrapping\tthat was a tabulator\nLINEBREAK!!!");
	}
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
		edi->offset.x += ((edi->mouse_pos.x - x) * edi->zoom); // IF ERRORS, use with -= instead
		edi->offset.y += ((edi->mouse_pos.y - y) * edi->zoom);
		//edi->offset.x += (x - edi->mouse_pos.x) * edi->zoom;
		//edi->offset.y += (y - edi->mouse_pos.y) * edi->zoom;
		edi->offset.x =  edi->offset.x < -BLOCKW * edi->map_size.x ? BLOCKW * -edi->map_size.x : edi->offset.x;
		edi->offset.x =  edi->offset.x > BLOCKW * edi->map_size.x ? BLOCKW * edi->map_size.x : edi->offset.x;
		edi->offset.y =  edi->offset.y < -BLOCKW * edi->map_size.y ? BLOCKW * -edi->map_size.y : edi->offset.y;
		edi->offset.y =  edi->offset.y > BLOCKW * edi->map_size.y ? BLOCKW * edi->map_size.y : edi->offset.y;
		edi->mouse_pos.x = x;
		edi->mouse_pos.y = y;
		//printf("offset %f %f\n", edi->offset.x, edi->offset.y);
		block_to_image(edi);
		mlx_pixel_put(edi->mlx_ptr, edi->mlx_win, edi->size.x / 2 - edi->offset.x, edi->size.y / 2 - edi->offset.y, 0xff0000);
	}
	else if (is_pressed(edi->button, MOUSE_DOWN, MOU_L))
		b_block_place(edi, x, y);
	//printf("motion in editor at %d %d\n", dot.x, dot.y);
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

int	editor_exit(t_editor *edit)
{
	tool_exit(edit->toolbar);
	return (0);
}
