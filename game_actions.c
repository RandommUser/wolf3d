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

static void	player_rota(t_player *player, PRECISION dir)
{
	t_pdot	oplane;
	t_pdot	odir;
	t_pdot	angle;
	// add pre-calculated sin and cos?

	angle.x = sin(dir);// * 0.01745329251);
	angle.y = cos(dir);// * 0.01745329251);
	oplane = player->plane;
	odir = player->dir;
	player->dir.x = player->dir.x * angle.y - player->dir.y * angle.x;
	player->dir.y = odir.x * angle.x + player->dir.y * angle.y;

	//planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    //planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	player->plane.x = player->plane.x * angle.y - player->plane.y * angle.x;
	player->plane.y = oplane.x * angle.x + player->plane.y * angle.y;
}

int	player_move(t_game *game)
{
	t_pdot		move;
	//t_pdot		temp;
	//t_pdot		rot;
	PRECISION	turn;

	move = pdot(0, 0);
	turn = 0;
	if (is_pressed(game->key, KEY_DOWN, K_W))
		move.y += MOVE_SPEED;
	if (is_pressed(game->key, KEY_DOWN, K_S))
		move.y -= MOVE_SPEED;
	if (is_pressed(game->key, KEY_DOWN, K_A))
		move.x -= MOVE_SPEED;
	if (is_pressed(game->key, KEY_DOWN, K_D))
		move.x += MOVE_SPEED;
	if (is_pressed(game->key, KEY_DOWN, K_AR))
		turn -= TURN_RATE;
	if (is_pressed(game->key, KEY_DOWN, K_AL))
		turn += TURN_RATE;
	if (is_pressed(game->key, KEY_DOWN, K_R))
	{
		game->player = player_reset();
		return (1);
	}
	if (!move.y && !move.x && !turn)
		return (0);
	turn *= is_pressed(game->key, KEY_DOWN, L_SHFT) ? 2 : 1;
	player_rota(&game->player, turn);
	move.x *= is_pressed(game->key, KEY_DOWN, L_SHFT) ? 2 : 1;
	move.y *= is_pressed(game->key, KEY_DOWN, L_SHFT) ? 2 : 1;
	game->player.pos.x += game->player.dir.x * move.y; // ADD COLLION TEST
	game->player.pos.y += game->player.dir.y * move.y;
	//game->player.pos.x += game->player.dir.x * move.x + game->player.dir.y * move.x; // not quite
	//game->player.pos.y += game->player.dir.x * move.x + game->player.dir.y * move.x;
	/*game->player.rot += turn * 60;
	game->player.rot += game->player.rot < 0 ? 360 : 0;
	game->player.rot -= game->player.rot > 359 ? 360 : 0;
	rot.x = cos(game->player.rot * 0.01745329251);	// (pi / 180)
	rot.y = sin(game->player.rot * 0.01745329251);
	//printf("rot %f %f\n", rot.x, rot.y);
	temp.x = move.x * rot.x - move.y * rot.y;
	temp.y = move.x * rot.y + move.y * rot.x;
	//printf("%d | %f %f\n", turn, temp.x, temp.y);
	game->player.pos.x += temp.x;
	game->player.pos.y += temp.y; // not moving??*/
	
	return (1);
}
