/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mloops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:10:58 by phakakos          #+#    #+#             */
/*   Updated: 2021/02/18 15:10:58 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	pause_keys(t_game *game, int key, void f(t_game *, char))
{
	if (key == K_AU || key == K_AD)
	{
		game->mselect += key == K_AU ? -1 : 1;
		f(game, 0);
	}
	else if (key == K_ENT)
		f(game, '+');
}

int			game_key_down(int key, t_game *game)
{
	if (key == ESC_KEY)
	{
		t_mlx_delete(&game->mlx);
		good_exit(EXIT_SUCCESS, "esc exit");
	}
	if (game->state == RUNNING)
	{
		key_controls(game->key, KEY_DOWN, key, '+');
		if (key == K_V)
			game->verbose = game->verbose ? 0 : 1;
		if (key == K_C)
			game->player.collision = game->player.collision ? 0 : 1;
		if (key == K_P)
			pause_menu(game, 0);
	}
	else if (game->state == START_SCREEN && key == K_ENT)
		game->state = RUNNING;
	else if (game->state == PAUSED)
		pause_keys(game, key, &pause_menu);
	else if (game->state == END_SCREEN)
		pause_keys(game, key, &end_menu);
	return (0);
}

int			game_key_up(int key, t_game *game)
{
	return (key_controls(game->key, KEY_DOWN, key, '-'));
}
