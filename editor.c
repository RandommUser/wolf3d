/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 11:42:26 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/11 11:42:27 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static	t_mapb	*map_init(t_editor *edit)
{
	t_dot	spot;

	edit->start = block_add(edit, B_START + BLOCKH, dot(0, 0), ft_strdup(MAP_SPAWN_FLAG));
	spot.y = -(edit->map_size.y) - 1;
	while (++spot.y <= edit->map_size.y)
	{
		spot.x = -(edit->map_size.x) - 1;
		while (++spot.x <= edit->map_size.x)
		{
			if (block_edit(edit, B_EMPTY, spot, NULL))
				printf("block added %d %d\n", spot.x, spot.y);
		}
	}
	block_edit(edit, B_END + BLOCKSE, dot(0, 5), ft_strdup(MAP_END_FLAG));
	return (edit->start);
}

static t_editor	editor_init(int width, int height, void **img)
{
	t_editor	ret;

	ret.size.x = width;
	ret.size.y = height;
	ret.mlx_img = img;
	ret.name = NULL;
	ret.next = NULL;
	ret.desc = NULL;
	ret.version = NULL;
	ret.offset.x = 0;
	ret.offset.y = 0;
	ret.map_size = dot(MAP_SIZE, MAP_SIZE);
	ret.zoom = 1;
	ret.select = B_FLOOR;
	ret.port = 1;
	ft_memset(ret.key, NO_KEY,sizeof(int[KEY_DOWN]));
	ft_memset(ret.button, NO_KEY, sizeof(int[MOUSE_DOWN]));
	ret.start = map_init(&ret);
	ret.edit = NULL;
	ret.toolbar = NULL;
	//block_add(&ret, B_START + BLOCKH, dot(0, 0), MAP_SPAWN_FLAG);
	//block_edit(&ret, B_END + BLOCKSE, dot(0, 5), MAP_END_FLAG);
	return (ret);
}

static	t_toolbar toolbar_init(int width, int height, t_editor *edit)
{
	t_toolbar bar;

	bar.hover = -1;
	bar.size = dot(width, height);
	bar.editor = edit;
	bar.mlx_ptr = NULL;
	bar.mlx_win = NULL;
	return (bar);
}

void	editor(char *arg)
{
	void		*mlx_ptr;
	t_editor	editor;
	t_toolbar	toolbar;
	t_box		box;
	void		*windows[2];
	void		*textures[EDI_BLOCK * 3];

	if (!(mlx_ptr = mlx_init()))
		err_exit(ERR_MLX, "editor mlx_ptr init failed");
	if (!(windows[0] = mlx_new_window(mlx_ptr, EDI_WIDTH, EDI_HEIGHT, "Map editor")))
		err_exit(ERR_MLX, "editor main window start failed");
	if (!(windows[1] = mlx_new_window(mlx_ptr, BAR_WIDTH, BAR_HEIGHT, "Editor toolbar")))
		err_exit(ERR_MLX, "editor toolbar window start failed");
	editor = editor_init(EDI_WIDTH, EDI_HEIGHT, textures);
	editor.mlx_ptr = mlx_ptr;
	editor.mlx_win = windows[0];
	if (!(editor.map_img = mlx_new_image(mlx_ptr, EDI_WIDTH, EDI_HEIGHT)))
		err_exit(ERR_MLX, "editor map_img start failed");
	editor.map_data = (int*)mlx_get_data_addr(editor.map_img, &box.bpp, &box.line_size, &box.endian);
	if (arg)
		map_reader(arg, &editor);
	text_init(mlx_ptr, textures, BLOCKW, BLOCKW);

	toolbar = toolbar_init(BAR_WIDTH, BAR_HEIGHT, &editor);
	toolbar.mlx_ptr = mlx_ptr;
	toolbar.mlx_win = windows[1];
	editor.toolbar = &toolbar;

	mlx_mouse_hook(windows[0], &mouse, &editor);
	mlx_key_hook(windows[0], &key, &editor);

	mlx_hook(windows[0], KEY_PRESS, 0, &key_press, &editor);
	mlx_hook(windows[0], KEY_RELEASE, 0, &key_release, &editor);
	mlx_hook(windows[0], BUTTON_PRESS, 0, &button_pressed, &editor);
	mlx_hook(windows[0], BUTTON_RELEASE, 0, &button_released, &editor);
	mlx_hook(windows[0], MOTION_NOTIFY, 0, &motion_notify, &editor);
	mlx_hook(windows[0], ENTER_NOTIFY, 0, &enter_notify, &editor);
	mlx_hook(windows[0], LEAVE_NOTIFY, 0, &leave_notify, &editor);

	mlx_hook(windows[1], BUTTON_PRESS, 0, &bar_mouse_click, &toolbar);
	mlx_hook(windows[1], MOTION_NOTIFY, 0, &bar_mouse_hover, &toolbar);

	block_to_image(&editor);
	tool_render(&toolbar);
	mlx_loop(mlx_ptr);
}
