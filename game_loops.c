/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:05:17 by phakakos          #+#    #+#             */
/*   Updated: 2020/12/15 16:05:18 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	game_loop(t_game *game)
{
	static clock_t	start;
	static clock_t	fps;
	static t_dot	ps;
	static int		frames;
	clock_t			curr;
	double			d;

	if (game->state != RUNNING)
		return (0);
	if (!start)
	{
		start = clock();
		fps = start;
		mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
	}	
	curr = clock();
	d = ((double)curr - start)/CLOCKS_PER_SEC*6;
	if (d >= game->frame)
	{
		// ACTIONS HERE
		if (player_move(game))
		{
			//mlx_pixel_place(game->mlx, dot(game->player.pos.x, game->player.pos.y), 0xffffff);
			image_set(game->image[0], 0x000000);
			image_set(game->image[1], 0x000000);
			raycast(*game);
			image_combine(game->image[0], game->image[1], 0x000000);
			//mlx_line_to_image(game->image, dot(0, 0), dot(GWIDTH, GHEIGHT), 0xffffff);
			mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
			if (game->verbose)
				printf("player is at %f %f\n", game->player.pos.x, game->player.pos.y);
			//	printf("player is at %f %f \nplane %f %f | dir %f %f | rot %f\n", game->player.pos.x, game->player.pos.y,
			//	game->player.plane.x, game->player.plane.y, game->player.dir.x, game->player.dir.y, game->player.rot);
		}
		//printf("took %lf > %f\n", d, game->frame);
		start = curr;
		d = ((double)curr - fps)/CLOCKS_PER_SEC*6;
		//printf("collected %lf\n", d);
		if (d >= 1)
		{
			ps.x++;
			ps.y = ++frames;
			//mlx_pixel_place(game->mlx, ps, frames == FRAMECAP ? 0x00ff00 : 0xff0000);
			if (ps.x == game->mlx.size.x - 1)
				ps.x = 0;
			//printf("frames: %d\n", ++frames);
			frames = 0;
			fps = curr;
		}
		else
			frames++;
	}
	return (0);
}

int	game_key_down(int key, t_game *game)
{
	if (key == ESC_KEY)
	{
		t_mlx_delete(&game->mlx);
		good_exit(EXIT_SUCCESS, "esc exit");
	}
	if (game->state == RUNNING)
	{
		if (key_controls(game->key, KEY_DOWN, key, '+') == 1 && game->verbose)
		{
			printf("down:");
			for (int i = 0; i < KEY_DOWN; i++)
			{
				printf(" %d", game->key[i]);
			}
			printf("\n");
		}
		if (key == K_V)
			game->verbose = game->verbose ? 0 : 1;
		if (key == K_1)
			mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
		if (key == K_2)
			mlx_image_place(game->mlx, game->image[1].img_ptr, dot(0, 0));	
		if (key == K_C)
			game->player.collision = game->player.collision ? 0 : 1;
	}
	else if (game->state == START_SCREEN)
	{
		if (key == K_ENT)
		{
			game->state = RUNNING;

		}
	}
	return (0);
}

int	game_key_up(int key, t_game *game)
{
	if(key_controls(game->key, KEY_DOWN, key, '-') && game->verbose)
		printf("up: %d\n", key);
	return (0);
}

/*
int	game_button(int x, int y, int button, t_game *game) // not used?
{

	return (0);
}*/
