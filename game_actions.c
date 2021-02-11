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
		if (new.x > old.x && is_wall(start, NULL, spot = dot(dround(new.x +
			PSIZE), dround(new.y)))) new.x = spot.x - PSIZE;
		else if (is_wall(start, NULL, spot = dot(dround(new.x - PSIZE),
			dround(new.y)))) new.x = dround(new.x) + PSIZE;
	}
	if (new.y != old.y)
	{
		if (new.y > old.y && is_wall(start, NULL, spot = dot(dround(new.x),
			dround(new.y + PSIZE)))) new.y = spot.y - PSIZE;
		else if (is_wall(start, NULL, spot = dot(dround(new.x), dround(new.y -
			PSIZE)))) new.y = dround(new.y) + PSIZE;
	}
	return (new);
}

static void	player_rota(t_player *player, t_precision dir)
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

int	player_move(t_game *game)
{
	t_pdot		opos;
	t_pdot		move;
	t_pdot		movement;
	t_pdot		tplane;
	t_pdot		tdir;
	t_precision	turn;
	static t_precision	turning;//remove?
	int			view;

	move = pdot(0, 0);
	turn = 0;
	view = 0;
	if (is_pressed(game->key, KEY_DOWN, K_AU))
		view += HEAD_TILT;
	if (is_pressed(game->key, KEY_DOWN, K_AD))
		view -= HEAD_TILT;
	if (view || game->player.look != game->mlx.size.y / 2)
	{
		game->player.look += view <= 0 && game->player.look > game->mlx.size.y / 2 ? -HEAD_TILT : 0;
		game->player.look += view >= 0 && game->player.look < game->mlx.size.y / 2 ? HEAD_TILT : 0;
		game->player.look += view;
		view = !view ? 1 : view;
		game->player.look = game->player.look < 0 ? 0 : game->player.look;
		game->player.look = game->player.look > game->mlx.size.y - 1 ? game->mlx.size.y - 1 : game->player.look;
	}
	if (is_pressed(game->key, KEY_DOWN, K_W))
		move.y += MOVE_SPEED;
	if (is_pressed(game->key, KEY_DOWN, K_S))
		move.y -= MOVE_SPEED;
	if (is_pressed(game->key, KEY_DOWN, K_A))
		move.x += MOVE_SPEED;
	if (is_pressed(game->key, KEY_DOWN, K_D))
		move.x -= MOVE_SPEED;
	if (is_pressed(game->key, KEY_DOWN, K_AR))
		turn -= TURN_RATE;
	if (is_pressed(game->key, KEY_DOWN, K_AL))
		turn += TURN_RATE;
	if (is_pressed(game->key, KEY_DOWN, K_R))
	{
		game->player = player_reset(game);
		return (1);
	}
	if (!view && !move.y && !move.x && !turn)
		return (0);
	opos = game->player.pos;
	turn *= is_pressed(game->key, KEY_DOWN, L_SHFT) ? 2 : 1;
	turning += turn;
	if (game->verbose)
		printf("turnig %f\n", turning);
	player_rota(&game->player, turn);
	move.x *= is_pressed(game->key, KEY_DOWN, L_SHFT) ? 2 : 1;
	move.y *= is_pressed(game->key, KEY_DOWN, L_SHFT) ? 2 : 1;
	movement.x = game->player.dir.x * move.y;
	movement.y = game->player.dir.y * move.y;
	if (move.x)
	{
		tplane = game->player.plane;
		tdir = game->player.dir;
		turn = move.x < 0 ? -1.575 : 1.575;
		move.x = ft_fabs(move.x);
		if (game->verbose)
			printf("turn %f\n", turn);
		player_rota(&game->player, turn);
		movement.x += game->player.dir.x * move.x;
		movement.y += game->player.dir.y * move.x;
		game->player.dir = tdir;
		game->player.plane = tplane;
	}
	game->player.pos.x += movement.x;
	game->player.pos.y += movement.y;
	game->player.pos = collision(game, game->map.start, game->player.pos, opos);
	return (1);
}
