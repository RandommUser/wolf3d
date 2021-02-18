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

static t_pdot	collision(t_game *game, t_mapb *start, t_pdot new, t_pdot old)
{
	t_dot	spot;

	if (!game->player.collision)
		return (new);
	if (new.x != old.x)
	{
		if (new.x > old.x && is_wall(start, NULL, (spot = dot(dround(new.x +
			PSIZE), dround(new.y)))))
			new.x = spot.x - PSIZE;
		else if (is_wall(start, NULL, (spot = dot(dround(new.x - PSIZE),
			dround(new.y)))))
			new.x = dround(new.x) + PSIZE;
	}
	if (new.y != old.y)
	{
		if (new.y > old.y && is_wall(start, NULL, (spot = dot(dround(new.x),
			dround(new.y + PSIZE)))))
			new.y = spot.y - PSIZE;
		else if (is_wall(start, NULL, (spot = dot(dround(new.x), dround(new.y -
			PSIZE)))))
			new.y = dround(new.y) + PSIZE;
	}
	return (new);
}

static void		player_rota(t_player *player, t_precision dir)
{
	t_pdot	oplane;
	t_pdot	odir;
	t_pdot	angle;

	angle.x = sin(dir);
	angle.y = cos(dir);
	oplane = player->plane;
	odir = player->dir;
	player->dir.x = player->dir.x * angle.y - player->dir.y * angle.x;
	player->dir.y = odir.x * angle.x + player->dir.y * angle.y;
	player->plane.x = player->plane.x * angle.y - player->plane.y * angle.x;
	player->plane.y = oplane.x * angle.x + player->plane.y * angle.y;
}

static t_move	read_mov(t_game *game, t_move mov)
{
	if (is_pressed(game->key, KEY_DOWN, K_AU))
		mov.view += HEAD_TILT;
	if (is_pressed(game->key, KEY_DOWN, K_AD))
		mov.view -= HEAD_TILT;
	if (mov.view || game->player.look)
	{
		game->player.look += mov.view <= 0 && game->player.look > 0 ?
			-HEAD_TILT : 0;
		game->player.look += mov.view >= 0 && game->player.look < 0 ?
			HEAD_TILT : 0;
		game->player.look += mov.view;
		mov.view = 1;
		game->player.look = game->player.look < -game->mlx.size.y / 2 ?
			-game->mlx.size.y / 2 : game->player.look;
		game->player.look = game->player.look > game->mlx.size.y / 2 ?
			game->mlx.size.y / 2 : game->player.look;
	}
	mov.move.y += is_pressed(game->key, KEY_DOWN, K_W) ? MOVE_SPEED : 0;
	mov.move.y += is_pressed(game->key, KEY_DOWN, K_S) ? -MOVE_SPEED : 0;
	mov.move.x += is_pressed(game->key, KEY_DOWN, K_A) ? MOVE_SPEED : 0;
	mov.move.x += is_pressed(game->key, KEY_DOWN, K_D) ? -MOVE_SPEED : 0;
	mov.turn += is_pressed(game->key, KEY_DOWN, K_AL) ? TURN_RATE : 0;
	mov.turn += is_pressed(game->key, KEY_DOWN, K_AR) ? -TURN_RATE : 0;
	return (mov);
}

static t_move	p_move(t_game *game, t_move mov)
{
	mov.move.x *= is_pressed(game->key, KEY_DOWN, L_SHFT) ? 2 : 1;
	mov.move.y *= is_pressed(game->key, KEY_DOWN, L_SHFT) ? 2 : 1;
	mov.movement.x = game->player.dir.x * mov.move.y;
	mov.movement.y = game->player.dir.y * mov.move.y;
	if (mov.move.x)
	{
		mov.tplane = game->player.plane;
		mov.tdir = game->player.dir;
		mov.turn = mov.move.x < 0 ? -1.575 : 1.575;
		mov.move.x = ft_fabs(mov.move.x);
		player_rota(&game->player, mov.turn);
		mov.movement.x += game->player.dir.x * mov.move.x;
		mov.movement.y += game->player.dir.y * mov.move.x;
		game->player.dir = mov.tdir;
		game->player.plane = mov.tplane;
	}
	game->player.pos.x += mov.movement.x;
	game->player.pos.y += mov.movement.y;
	return (mov);
}

int				player_move(t_game *game)
{
	t_move	mov;

	mov.move = pdot(0, 0);
	mov.turn = 0;
	mov.view = 0;
	mov = read_mov(game, mov);
	if (!mov.view && !mov.move.y && !mov.move.x && !mov.turn)
		return (0);
	mov.opos = game->player.pos;
	mov.turn *= is_pressed(game->key, KEY_DOWN, L_SHFT) ? 2 : 1;
	player_rota(&game->player, mov.turn);
	mov = p_move(game, mov);
	game->player.pos = collision(game, game->map.start, game->player.pos,
		mov.opos);
	return (1);
}
