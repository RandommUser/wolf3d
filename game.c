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

int		game_exit(t_game *game)
{
	t_mlx_delete(&game->mlx);
	good_exit(EXIT_SUCCESS, NULL);
	return (1);
}

t_game	game_start(void)
{
	t_game	game;

	log_reset(&game.key[0], KEY_DOWN, NO_KEY);
	game.map = map_empty();
	game.frame = (t_precision)(1.0 / (FRAMECAP)) * CLOCKS_PER_SEC;
	game.verbose = 0;
	game.state = START_SCREEN;
	game.mselect = 0;
	game.menu = MENU_PAUSE;
	printf("frametime %lf'\n", game.frame / CLOCKS_PER_SEC);
	return (game);
}

void	game(char *name)
{
	t_game	game;

	game = game_start();
	if (!map_reader(name, &game.map))
		err_exit(ERR_PARA, "Bad map game()");
	if (!(game.mlx.mlx_ptr = mlx_init()))
		err_exit(ERR_MLX, "MLX failed to init game()");
	//game.player.pos = start square
	printf("map path is %s\n", game.map.path);
	game.mlx = mlx_start(game.mlx.mlx_ptr, GWIDTH, GHEIGHT, "Wolf3D");
	game.player = player_reset(&game);
	game.image[0] = mlx_image(game.mlx, game.mlx.size, 0x000000);
	game.image[1] = mlx_image(game.mlx, game.mlx.size, 0x000000);

	raycast(game);
	image_combine(game.image[0], game.image[1], 0x000000);
	mlx_image_place(game.mlx, game.image[0].img_ptr, dot(0, 0));
	write_to_screen(game.mlx, dot(game.mlx.size.x / 2 - (int)(ft_strlen(game.map.name) / 2) * TEXT_WIDTH, 50), MSELECTED, game.map.name);
	write_to_screen(game.mlx, dot(100, 200), MNORMAL, game.map.desc);
	write_to_screen(game.mlx, dot(game.mlx.size.x / 2 - (int)(ft_strlen("Press Enter to start") / 2) * TEXT_WIDTH, game.mlx.size.y - 50), MNORMAL, "Press Enter to start");

	mlx_loop_hook(game.mlx.mlx_ptr, &game_loop, &game);
	mlx_hook(game.mlx.mlx_win, KEY_PRESS, 0, &game_key_down, &game);
	mlx_hook(game.mlx.mlx_win, KEY_RELEASE, 0, &game_key_up, &game);
	mlx_hook(game.mlx.mlx_win, WINDOW_CLOSE, 0, &game_exit, &game);
	mlx_loop(game.mlx.mlx_ptr);
}
