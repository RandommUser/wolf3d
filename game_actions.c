/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:05:33 by phakakos          #+#    #+#             */
/*   Updated: 2020/12/15 16:05:34 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
/*
int	player_turn(t_game *game)
{

	return (0);
}
*/
int	player_move(t_game *game)
{
	t_dot	move;
	t_pdot	temp;
	t_pdot	rot;
	int		turn;

	move = dot(0, 0);
	turn = 0;
	if (is_pressed(game->key, KEY_DOWN, K_W))
		move.y -= MOVE_SPEED;	// change to ++
	if (is_pressed(game->key, KEY_DOWN, K_S))
		move.y += MOVE_SPEED;	// change to --
	if (is_pressed(game->key, KEY_DOWN, K_A))
		move.x -= MOVE_SPEED;
	if (is_pressed(game->key, KEY_DOWN, K_D))
		move.x += MOVE_SPEED;
	if (is_pressed(game->key, KEY_DOWN, K_AR))
		turn += TURN_RATE;
	if (is_pressed(game->key, KEY_DOWN, K_AL))
		turn -= TURN_RATE;
	if (!move.y && !move.x && !turn)
		return (0);
	move.x *= is_pressed(game->key, KEY_DOWN, L_SHFT) ? 2 : 1;
	move.y *= is_pressed(game->key, KEY_DOWN, L_SHFT) ? 2 : 1;
	game->player.rot += turn;
	game->player.rot += game->player.rot < 0 ? 360 : 0;
	game->player.rot -= game->player.rot > 359 ? 360 : 0;
	rot.x = cos(game->player.rot * 0.01745329251);	// (pi / 180)
	rot.y = sin(game->player.rot * 0.01745329251);
	//printf("rot %f %f\n", rot.x, rot.y);
	temp.x = move.x * rot.x - move.y * rot.y;
	temp.y = move.x * rot.y + move.y * rot.x;
	//printf("%d | %f %f\n", turn, temp.x, temp.y);
	game->player.pos.x += temp.x;
	game->player.pos.y += temp.y; // not moving??
	return (1);
}
