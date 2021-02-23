/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:06:46 by phakakos          #+#    #+#             */
/*   Updated: 2020/12/15 15:06:48 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_game	game_init(void)
{
	t_game	game;

	log_reset(&game.key[0], KEY_DOWN, NO_KEY);
	game.map = map_empty();
	game.frame = (t_precision)(1.0 / (FRAMECAP)) * CLOCKS_PER_SEC;
	game.verbose = 0;
	game.state = START_SCREEN;
	game.mselect = 0;
	game.menu = MENU_PAUSE;
	return (game);
}

void			start_menu(t_game *game)
{
	game->state = START_SCREEN;
	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.mlx_win);
	image_set(game->image[0], 0x000000);
	image_set(game->image[1], 0x000000);
	raycast(*game);
	image_combine(game->image[0], game->image[1], 0x000000);
	mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
	write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - (int)(ft_strlen(
		game->map.name) / 2) * TEXT_WIDTH, 50), MSELECTED, game->map.name);
	write_to_screen(game->mlx, dot(100, 200), MNORMAL, game->map.desc);
	write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - (int)(ft_strlen(
		"Press Enter to start") / 2) * TEXT_WIDTH, game->mlx.size.y - 50),
		MNORMAL, "Press Enter to start");
}

static t_game	game_text(t_game game)
{
	game.text[0] = ft_memalloc((sizeof(int) * 4));
	game.text[1] = ft_memalloc((sizeof(int) * 4));
	game.text[2] = ft_memalloc((sizeof(int) * 4));
	game.text[3] = ft_memalloc((sizeof(int) * 4));
	wall_text(game.text[0], dot(2, 2), 0xad0864, 0x288217);
	wall_text(game.text[1], dot(2, 2), 0xb0b02b, 0xed390d);
	wall_text(game.text[2], dot(2, 2), 0x0dce5c, 0x717b75);
	wall_text(game.text[3], dot(2, 2), 0x00f0ec, 0xf000e5);
	return (game);
}

static void		game_start(t_game game)
{
	game = game_text(game);
	start_menu(&game);
	mlx_loop_hook(game.mlx.mlx_ptr, &game_loop, &game);
	mlx_hook(game.mlx.mlx_win, KEY_PRESS, 0, &game_key_down, &game);
	mlx_hook(game.mlx.mlx_win, KEY_RELEASE, 0, &game_key_up, &game);
	mlx_hook(game.mlx.mlx_win, WINDOW_CLOSE, 0, &game_exit, &game);
	mlx_loop(game.mlx.mlx_ptr);
}

void			game(char *name)
{
	t_game	game;

	game = game_init();
	if (!map_reader(name, &game.map))
		err_exit(ERR_PARA, "Invalid map");
	if (!(game.mlx.mlx_ptr = mlx_init()))
		err_exit(ERR_MLX, "MLX failed to init game()");
	game.mlx = mlx_start(game.mlx.mlx_ptr, GWIDTH, GHEIGHT, "Wolf3D");
	game.player = player_reset(&game);
	game.image[0] = mlx_image(game.mlx, game.mlx.size, 0x000000);
	game.image[1] = mlx_image(game.mlx, game.mlx.size, 0x000000);
	game_start(game);
}
