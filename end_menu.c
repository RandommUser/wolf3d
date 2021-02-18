/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:38:58 by phakakos          #+#    #+#             */
/*   Updated: 2021/02/12 17:39:02 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	men_init(t_game *game, int menu, int opt)
{
	int	ret;

	log_reset(game->key, KEY_DOWN, NO_KEY);
	game->state = END_SCREEN;
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

static void	em_opt(t_game *game, int options, int selected)
{
	static char	*msg[5] = {
		"YOU FOUND THE GOAL!!!", "Next map", "Restart", "Exit", "Last map"
	};

	p_print(game, msg[0], 5, MNORMAL);
	if (options == 3)
	{
		if (selected == 0)
			p_print(game, msg[selected + 1], 3 - selected * 2, MSELECTED);
		else
			p_print(game, msg[1], 3, MNORMAL);
	}
	else
		p_print(game, msg[4], 3, MNORMAL);
	if (selected == 1)
		p_print(game, msg[selected + 1], 3 - selected * 2, MSELECTED);
	else
		p_print(game, msg[2], 1, MNORMAL);
	if (selected == 2)
		p_print(game, msg[selected + 1], 3 - selected * 2, MSELECTED);
	else
		p_print(game, msg[3], -1, MNORMAL);
}

static void	end_select(t_game *game, int selected)
{
	char	*next;

	game->state = RUNNING;
	if (selected == 0)
	{
		if (!(next = ft_strjoin(game->map.path, game->map.next)) ||
			!map_reader(next, &game->map))
			err_exit(ERR_PARA, "Invalid map, exiting");
		free(next);
		game->player = player_reset(game);
		start_menu(game);
	}
	else if (selected == 1)
	{
		game->player = player_reset(game);
		start_menu(game);
	}	
	else if (selected == 2)
		game_key_down(ESC_KEY, game);
}

void		end_menu(t_game *game, char action)
{
	int		selected;
	int		options;

	options = !ft_strcmp(game->map.next, MAP_END) ? 2 : 3;
	selected = men_init(game, END_SCREEN, options);
	selected += options == 2 ? 1 : 0;
	mlx_image_place(game->mlx, game->image[0].img_ptr, dot(0, 0));
	em_opt(game, options, selected);
	if (action == '+')
		end_select(game, selected);
}
