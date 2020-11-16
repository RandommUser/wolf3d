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
	ret.zoom = 1;
	ret.select = 0;
	ret.port = 1;
	ft_memset(ret.key, NO_KEY,sizeof(int[KEY_DOWN]));
	ft_memset(ret.button, NO_KEY, sizeof(int[MOUSE_DOWN]));
	ret.start = block_add(NULL, B_START + BLOCKH, dot(0, 0), MAP_SPAWN_FLAG);
	block_edit(ret.start, B_END + BLOCKSE, dot(0, 5), MAP_END_FLAG);
	return (ret);
}

void	editor(void)
{
	void		*mlx_ptr;
	t_editor	editor;
	//t_toolbar	toolbar;
	t_box		box;
	void		*windows[2];
	void		*textures[EDI_BLOCK * 3];

	if (!(mlx_ptr = mlx_init()))
		err_exit(ERR_MLX, "editor mlx_ptr init failed");
	if (!(windows[0] = mlx_new_window(mlx_ptr, EDI_WIDTH, EDI_HEIGHT, "Map editor")))
		err_exit(ERR_MLX, "editor main window start failed");
	//if (!(windows[1] = mlx_new_window(mlx_ptr, BAR_WIDTH, BAR_HEIGHT, "Editor toolbar")))
	//	err_exit(ERR_MLX, "editor toolbar window start failed");
	editor = editor_init(EDI_WIDTH, EDI_HEIGHT, textures);
	editor.mlx_ptr = mlx_ptr;
	editor.mlx_win = windows[0];
	if (!(editor.map_img = mlx_new_image(mlx_ptr, EDI_WIDTH, EDI_HEIGHT)))
		err_exit(ERR_MLX, "editor map_img start failed");
	editor.map_data = (int*)mlx_get_data_addr(editor.map_img, &box.bpp, &box.line_size, &box.endian);
	text_init(mlx_ptr, textures, BLOCKW, BLOCKW);
	mlx_mouse_hook(windows[0], &mouse, &editor);
	mlx_key_hook(windows[0], &key, &editor);

	mlx_hook(windows[0], KEY_PRESS, 0, &key_press, &editor);
	mlx_hook(windows[0], KEY_RELEASE, 0, &key_release, &editor);
	mlx_hook(windows[0], BUTTON_PRESS, 0, &button_pressed, &editor);
	mlx_hook(windows[0], BUTTON_RELEASE, 0, &button_released, &editor);
	mlx_hook(windows[0], MOTION_NOTIFY, 0, &motion_notify, &editor);
	mlx_hook(windows[0], ENTER_NOTIFY, 0, &enter_notify, &editor);
	mlx_hook(windows[0], LEAVE_NOTIFY, 0, &leave_notify, &editor);
	block_to_image(&editor);
	mlx_loop(mlx_ptr);
}
