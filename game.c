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
	game.frame = 1 / FRAMECAP;
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
	game.mlx = mlx_start(game.mlx.mlx_ptr, GWIDTH, GHEIGHT, "Wolf3D");

	mlx_hook(game.mlx.mlx_win, WINDOW_CLOSE, 0, &game_exit, &game);
	mlx_loop(game.mlx.mlx_ptr);
}