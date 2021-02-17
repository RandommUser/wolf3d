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

static void		input_print(t_editor *edit, char *smsg, char *cmsg)
{
	block_to_image(edit);
	write_to_screen(edit->mlx, dot(20, 10), 0x00ff00, smsg);
	mlx_do_sync(edit->mlx.mlx_ptr);
	ft_putstr(cmsg);
}

static void		*input_loop(t_editor *edit, char *smsg, char *cmsg, char *curr)
{
	char	*str;

	input_print(edit, smsg, cmsg);
	if (curr) // has old value
	{
		ft_putstr("or press Enter for current '");
		ft_putstr(curr);
		ft_putstr("'\n");
	}
	if (get_next_line(0, &str) != 1)
		err_exit(ERR_MEMORY, "input_loop gnl alloc error");
	if (str[0]) // good new value
	{
		free(curr);
		return (str);
	}
	free(str);
	if (curr)// has already a value, new input empty
		return (curr);
	else// no value, no input
	{
		ft_putstr("Please give an input!!\n");
		return (input_loop(edit, smsg, cmsg, curr));
	}
}

static void		map_save(t_editor *edit)
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

static int	param_check(char *str)
{
	static char	*valid[MAP_PARAMS + 1] = {
		MAP_SPAWN_FLAG, MAP_END_FLAG, "\0"
	};
	int	i;
	int	s;

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
	if (block->param) // has old value
	{
		ft_putstr("Press enter for current (");
		ft_putstr(block->param);
		ft_putstr(")\n");
	}
	if (get_next_line(0, &param) != 1)
		err_exit(ERR_MEMORY, "edit_param gnl error");
	if (!param[0]) // new input empty
	{
		free(param);
		param = ft_strdup(block->param); // alloc check, dup cause old gets freed
	}
	else if (!ft_strcmp(param, "NULL")) // input is "NULL"
	{
		free(param);
		param = NULL;
	}
	insert_param(edit, block, param);
}

static t_mapb	*block_read(t_editor *edi, int x, int y)//
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
	else if (block)//
	{//
		printf("Block X: %d Y: %d\n", block->pos.x, block->pos.y);//
		printf("Block: %d\n",block->block);//
		printf("Param: %s\n", block->param);//
		printf("Next: %p\n", block->next);//
	}//
	return (block);
}

static void		b_block_place(t_editor *edi, int x, int y)
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
	if (block_edit(&edi->map, edi->select, point, NULL))//
		printf("block placed at %d %d\n", point.x ,point.y);//
	block_to_image(edi);
}



int	key_press(int key, t_editor *edi) // THIS IS THE LAST ONE ?
{
	if (key_controls(edi->key, KEY_DOWN, key, '+'))//
	{//
		printf("pressed %d\n", key);//
		printf("currently pressed: [%d, %d, %d, %d, %d]\n",//
		edi->key[0],edi->key[1],edi->key[2],edi->key[3],edi->key[4]);//
	}//
	if (key == ESC_KEY)
	{
		map_delete(&edi->map);
		mlx_destroy_image(edi->mlx.mlx_ptr, edi->map_img);
		t_mlx_delete(&edi->mlx);
		good_exit(EXIT_SUCCESS, "esc quit");
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
		printf("ctrl + z\n");//
		block_undo(&edi->map, NULL, 0, NULL);
		key_controls(edi->key, KEY_DOWN, K_Z, '-');
		block_to_image(edi);
	}
	tool_render(edi->toolbar);
	return (0);
}

int key_release(int key, t_editor *edi)
{
	key_controls(edi->key, KEY_DOWN, key, '-');
	printf("released %d\n", key);//
	printf("currently pressed: [%d, %d, %d, %d, %d]\n",//
	edi->key[0],edi->key[1],edi->key[2],edi->key[3],edi->key[4]);//
	return (0);
}

int button_pressed(int button, int x, int y, t_editor *edi) // Limit listed buttons?
{
	if (button != MOU_S_D && button != MOU_S_U)
		key_controls(edi->button, MOUSE_DOWN, button, '+');
	printf("pressed %d at %d %d\n", button, x, y);//
	printf("currently pressed: [%d, %d]\n",//
	edi->button[0], edi->button[1]);//
	edi->mouse_pos = dot(x, y);
	if (button == MOU_L)
		b_block_place(edi, x, y);
	else if (button == MOU_R)
		edi->edit = block_read(edi, x, y);
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

int button_released(int button, int x, int y, t_editor *edi)
{
	printf("released %d at %d %d\n", button, x, y);//
	key_controls(edi->button, MOUSE_DOWN, button, '-');
	printf("pressed %d at %d %d\n", button, x, y);//
	printf("currently pressed: [%d, %d]\n",//
	edi->button[0], edi->button[1]);//
	return (0);
}

/* any mouse movement, anywhere*/
int	motion_notify(int x, int y, t_editor *edi)
{
	if (is_pressed(edi->button, MOUSE_DOWN, MOU_M))
	{
		edi->offset.x += ((edi->mouse_pos.x - x) * edi->zoom);
		edi->offset.y += ((edi->mouse_pos.y - y) * edi->zoom);

		edi->offset.x =  edi->offset.x < BLOCKW * edi->map.top.x ?
			BLOCKW * edi->map.top.x : edi->offset.x;
		edi->offset.x =  edi->offset.x > BLOCKW * edi->map.bottom.x ?
			BLOCKW * edi->map.bottom.x : edi->offset.x;
		edi->offset.y =  edi->offset.y < BLOCKW * edi->map.top.y ?
			BLOCKW * edi->map.top.y : edi->offset.y;
		edi->offset.y =  edi->offset.y > BLOCKW * edi->map.bottom.y ?
			BLOCKW * edi->map.bottom.y : edi->offset.y;
		edi->mouse_pos.x = x;
		edi->mouse_pos.y = y;
		block_to_image(edi);
		mlx_pixel_put(edi->mlx.mlx_ptr, edi->mlx.mlx_win, edi->size.x / 2 - edi->offset.x, edi->size.y / 2 - edi->offset.y, 0xff0000);//
	}
	else if (is_pressed(edi->button, MOUSE_DOWN, MOU_L))
		b_block_place(edi, x, y);
	return (0);
}

int	editor_exit(t_editor *edit)
{
	tool_exit(edit->toolbar);
	return (0);
}