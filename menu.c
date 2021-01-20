/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:03:13 by phakakos          #+#    #+#             */
/*   Updated: 2021/01/20 15:03:15 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	end_menu(t_game *game, char action)
{
	int		selected;
	int		options;
	char	*next;

	options = !ft_strcmp(game->map.next, MAP_END) ? 2 : 3;

	log_reset(game->key, KEY_DOWN, NO_KEY);
	log_reset(game->button, MOUSE_DOWN, NO_KEY); // is even used?
	game->mselect = game->menu != END_SCREEN ? 0 : game->mselect;
	game->menu = game->menu != END_SCREEN ? END_SCREEN : game->menu;
	selected = game->mselect % options;
	selected += selected < 0 ? options : 0;
	selected += !ft_strcmp(game->map.next, MAP_END) ? 1 : 0;
	if (action == '+')
	{
		game->state = RUNNING;
		if (selected == 0)
		{
			printf("start the next map\n");
			if (!(next = ft_strjoin(game->map.path, game->map.next)) || !map_reader(next, &game->map))
				err_exit(ERR_PARA, "Bad map game()");
			free(next);
			game->player = player_reset(game);
		}
		if (selected == 1)
			game->player = player_reset(game);
		if (selected == 2)
			game_key_down(ESC_KEY, game);
	}
	mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
	write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("YOU FOUND THE GOAL!!!") / 2 * TEXT_WIDTH, 100), MNORMAL, "YOU FOUND THE GOAL!!!");
	if (ft_strcmp(game->map.next, MAP_END))
	{
		if (selected == 0)
			write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Next map") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * 3), MSELECTED, "Next map");
		else
			write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Next map") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * 3), MNORMAL, "Next map");
	}
	else
	{
		write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("No next map") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * 3), MNORMAL, "No next map");
	}
	if (selected == 1)
		write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Restart map") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * 1), MSELECTED, "Restart map");
	else
		write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Restart map") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * 1), MNORMAL, "Restart map");
	if (selected == 2)
		write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Exit") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * -1), MSELECTED, "Exit");
	else
		write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Exit") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * -1), MNORMAL, "Exit");
}

void	pause_menu(t_game *game, char action)
{
	int	selected;

	log_reset(game->key, KEY_DOWN, NO_KEY);
	log_reset(game->button, MOUSE_DOWN, NO_KEY); // is even used?
	game->mselect = game->menu != MENU_PAUSE ? 0 : game->mselect;
	game->menu = game->menu != MENU_PAUSE ? MENU_PAUSE : game->menu;
	selected = game->mselect % 3;
	selected += selected < 0 ? 3 : 0;
	if (action == '+')
	{
		game->state = RUNNING;
		if (selected == 1)
			game->player = player_reset(game);
		if (selected == 2)
			game_key_down(ESC_KEY, game);
	}
	if (!action)
		printf("selection %d > %d > %d\n", game->mselect, selected, (int)ft_abs(game->mselect % 3));
	mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
	write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("PAUSED") / 2 * TEXT_WIDTH, 100), MNORMAL, "PAUSED");
	if (selected == 0)
		write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Continue") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * 3), MSELECTED, "Continue");
	else
		write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Continue") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * 3), MNORMAL, "Continue");
	if (selected == 1)
		write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Restart") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * 1), MSELECTED, "Restart");
	else
		write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Restart") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * 1), MNORMAL, "Restart");
	if (selected == 2)
		write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Exit") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * -1), MSELECTED, "Exit");
	else
		write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen("Exit") / 2 * TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * -1), MNORMAL, "Exit");
	
}
