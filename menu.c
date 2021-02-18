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

static int	men_init(t_game *game, int menu, int opt)
{
	int	ret;

	log_reset(game->key, KEY_DOWN, NO_KEY);
	game->state = PAUSED;
	game->mselect = game->menu != menu ? 0 : game->mselect;
	game->menu = game->menu != menu ? menu : game->menu;
	ret = game->mselect % opt;
	ret += ret < 0 ? opt : 0;
	return (ret);
}

static void	p_print(t_game *game, char *str, int y, int col)
{
	write_to_screen(game->mlx, dot(game->mlx.size.x / 2 - ft_strlen(str) / 2 *
		TEXT_WIDTH, game->mlx.size.y / 2 - TEXT_HEIGHT * y), col, str);
}

static char	*p_text(int i)
{
	static char	*msg[4] = {
		"PAUSED", "Continue", "Restart", "Exit the game"
	};

	if (i < 4)
		return (msg[i]);
	return (NULL);
}

void		pause_menu(t_game *game, char action)
{
	int	selected;

	selected = men_init(game, MENU_PAUSE, 3);
	if (action == '+')
	{
		game->state = RUNNING;
		if (selected == 1)
			game->player = player_reset(game);
		if (selected == 2)
			game_key_down(ESC_KEY, game);
	}
	mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
	p_print(game, p_text(0), 5, MNORMAL);
	if (selected == 0)
		p_print(game, p_text(selected + 1), 3 - selected * 2, MSELECTED);
	else
		p_print(game, p_text(1), 3, MNORMAL);
	if (selected == 1)
		p_print(game, p_text(selected + 1), 3 - selected * 2, MSELECTED);
	else
		p_print(game, p_text(2), 1, MNORMAL);
	if (selected == 2)
		p_print(game, p_text(selected + 1), 3 - selected * 2, MSELECTED);
	else
		p_print(game, p_text(3), -1, MNORMAL);
}
