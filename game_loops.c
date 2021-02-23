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

int			game_exit(t_game *game)
{
	t_mlx_delete(&game->mlx);
	free(game->text[0]);
	free(game->text[1]);
	free(game->text[2]);
	free(game->text[3]);
	good_exit(EXIT_SUCCESS, NULL);
	return (1);
}

static void	frame_draw(t_game *game)
{
	if (player_move(game))
	{
		if (is_goal(game->map.start, dot(dround(game->player.pos.x),
			dround(game->player.pos.y))))
			end_menu(game, 0);
		else
		{
			image_set(game->image[0], 0x000000);
			image_set(game->image[1], 0x000000);
			raycast(*game);
			image_combine(game->image[0], game->image[1], 0x000000);
		}
	}
	if (game->state == RUNNING)
		mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
}

static void	framerate(t_game *game, clock_t curr)
{
	static clock_t	fps;
	static int		frames;

	if (!fps)
		fps = curr + CLOCKS_PER_SEC;
	if (curr >= fps)
	{
		if (game->verbose)
		{
			ft_putstr("Frames: ");
			ft_putnbr(frames);
			ft_putstr("\n");
		}
		frames = 0;
		fps += CLOCKS_PER_SEC;
	}
	else
		frames++;
}

int			game_loop(t_game *game)
{
	static clock_t	start;
	clock_t			curr;

	if (game->state != RUNNING)
		return (PAUSED);
	curr = clock();
	if (!start)
	{
		start = curr;
		mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
	}
	if (curr >= start)
	{
		start = curr + game->frame;
		frame_draw(game);
		framerate(game, curr);
	}
	return (RUNNING);
}
