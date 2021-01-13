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
	log_reset(&game.button[0], MOUSE_DOWN, NO_KEY);
	game.player = player_reset();
	game.map = map_empty();
	game.frame = (float)1 / FRAMECAP;
	game.verbose = 0;
	game.mid = GHEIGHT / 2;
	printf("%f'\n", game.frame);
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
	game.mlx = mlx_start(game.mlx.mlx_ptr, GWIDTH, GHEIGHT, "Wolf3D");
	game.image = mlx_image(game.mlx, game.mlx.size, 0x000000);

	mlx_loop_hook(game.mlx.mlx_ptr, &game_loop, &game);
	mlx_hook(game.mlx.mlx_win, KEY_PRESS, 0, &game_key_down, &game);
	mlx_hook(game.mlx.mlx_win, KEY_RELEASE, 0, &game_key_up, &game);
	mlx_hook(game.mlx.mlx_win, WINDOW_CLOSE, 0, &game_exit, &game);
	mlx_loop(game.mlx.mlx_ptr);
}
