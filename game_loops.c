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

static void	frame_draw(t_game *game)
{
	if (player_move(game))
	{
		if (is_goal(game->map.start, dot(dround(game->player.pos.x),
			dround(game->player.pos.y))))
		{
			end_menu(game, 0);
			printf("found goal\n");//
		}
		else
		{
			image_set(game->image[0], 0x000000);
			image_set(game->image[1], 0x000000);
			raycast(*game);
			image_combine(game->image[0], game->image[1], 0x000000);
			if (game->verbose)//
				printf("player is at %f %f\n", game->player.pos.x, game->player.pos.y);//
		}
	}
	if (game->state == RUNNING)
		mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
}

int	game_loop(t_game *game)
{
	static clock_t	start;
	static clock_t	fps;//
	static int		frames;//
	clock_t			curr;
	static int		skipped;//

	if (game->state != RUNNING)
		return (PAUSED);
	curr = clock();
	if (!start)
	{
		start = curr;
		fps = start + CLOCKS_PER_SEC;
		mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
	}	
	if (curr >= start)
	{
		start = curr + game->frame;
		frame_draw(game);
		if (curr >= fps)//
		{//
			printf("frames: %d skipped: %d\n", frames, skipped);//
			frames = 0;//
			fps += CLOCKS_PER_SEC;//
			skipped = 0;//
		}//
		else//
			frames++;//
	}
	else//
		skipped++;//
	return (RUNNING);
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
		{//
			printf("down:");//
			for (int i = 0; i < KEY_DOWN; i++)//
				printf(" %d", game->key[i]);//
			printf("\n");//
		}//
		if (key == K_V)
			game->verbose = game->verbose ? 0 : 1; // leave in?
		if (key == K_1)//
			mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));//
		if (key == K_2)//
			mlx_image_place(game->mlx, game->image[1].img_ptr, dot(0, 0));//
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

int	game_key_up(int key, t_game *game)
{
	if(key_controls(game->key, KEY_DOWN, key, '-') && game->verbose)
		printf("up: %d\n", key);//
	return (0);
}
