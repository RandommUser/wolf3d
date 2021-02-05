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

static	t_mapb	*map_init(t_map *map)
{
	t_dot	spot;

	map->start = block_add(map, B_START + BLOCKH, dot(0, 0),
		ft_strdup(MAP_SPAWN_FLAG)); // no alloc checking
	spot.y = -(map->size.y) - 1;
	while (++spot.y <= map->size.y)
	{
		spot.x = -(map->size.x) - 1;
		while (++spot.x <= map->size.x)
		{
			if (block_edit(map, B_EMPTY, spot, NULL))
				printf("block added %d %d\n", spot.x, spot.y);
		}
	}
	block_edit(map, B_END + BLOCKSE, dot(0, 5),
		ft_strdup(MAP_END_FLAG)); // no alloc checking
	return (map->start);
}

static t_editor	editor_init(int width, int height, void **img)
{
	t_editor	ret;

	ret.size.x = width;
	ret.size.y = height;
	ret.mlx_img = img;
	ret.map = map_empty();
	ret.map.size = dot(MAP_SIZE, MAP_SIZE);
	ret.offset.x = 0;
	ret.offset.y = 0;
	ret.zoom = 1;
	ret.select = B_FLOOR;
	ret.port = 1;
	ft_memset(ret.key, NO_KEY,sizeof(int[KEY_DOWN]));
	ft_memset(ret.button, NO_KEY, sizeof(int[MOUSE_DOWN]));
	ret.map.start = map_init(&ret.map);
	ret.edit = NULL;
	ret.toolbar = NULL;
	return (ret);
}

static	t_toolbar toolbar_init(t_editor *edit)
{
	t_toolbar bar;

	bar.hover = -1;
	bar.editor = edit;
	return (bar);
}

static void	editor_loop_init(t_editor *editor, t_toolbar *toolbar)
{
	mlx_hook(editor->mlx.mlx_win, KEY_PRESS, 0, &key_press, editor);
	mlx_hook(editor->mlx.mlx_win, KEY_RELEASE, 0, &key_release, editor);
	mlx_hook(editor->mlx.mlx_win, BUTTON_PRESS, 0, &button_pressed, editor);
	mlx_hook(editor->mlx.mlx_win, BUTTON_RELEASE, 0, &button_released, editor);
	mlx_hook(editor->mlx.mlx_win, MOTION_NOTIFY, 0, &motion_notify, editor);
	mlx_hook(editor->mlx.mlx_win, WINDOW_CLOSE, 0, &editor_exit, editor);
	mlx_hook(toolbar->mlx.mlx_win, BUTTON_PRESS, 0, &bar_mouse_click, toolbar);
	mlx_hook(toolbar->mlx.mlx_win, MOTION_NOTIFY, 0, &bar_mouse_hover, toolbar);
	mlx_hook(toolbar->mlx.mlx_win, WINDOW_CLOSE, 0, &tool_exit, toolbar);
	mlx_hook(toolbar->mlx.mlx_win, KEY_PRESS, 0, &bar_key_press, toolbar);
}

void	editor(char *arg)
{
	void		*mlx_ptr;
	t_editor	editor;
	t_toolbar	toolbar;
	t_box		box;
	void		*textures[EDI_BLOCK * 3];

	editor = editor_init(EDI_WIDTH, EDI_HEIGHT, textures);
	if (arg && !map_reader(arg, &editor.map))
		err_exit(ERR_PARA, "Bad map\n");
	if (!(mlx_ptr = mlx_init()))
		err_exit(ERR_MLX, "editor mlx_ptr init failed");
	editor.mlx = mlx_start(mlx_ptr, EDI_WIDTH, EDI_HEIGHT, "Map editor");
	if (!(editor.map_img = mlx_new_image(mlx_ptr, EDI_WIDTH, EDI_HEIGHT)))
		err_exit(ERR_MLX, "editor map_img start failed");
	editor.map_data = (int*)mlx_get_data_addr(editor.map_img, &box.bpp,
		&box.line_size, &box.endian);
	tex_init(mlx_ptr, textures, BLOCKW, BLOCKW);
	toolbar = toolbar_init(&editor);
	toolbar.mlx = mlx_start(mlx_ptr, BAR_WIDTH, BAR_HEIGHT, "Editor toolbar");
	editor.toolbar = &toolbar;
	editor_loop_init(&editor, &toolbar);
	block_to_image(&editor);
	tool_render(&toolbar);
	mlx_loop(mlx_ptr);
}
