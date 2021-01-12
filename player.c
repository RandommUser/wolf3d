/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:25:04 by phakakos          #+#    #+#             */
/*   Updated: 2020/12/15 15:25:05 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_player	player_reset(void)
{
	t_player	player;

	player.rot = 0;
	player.pos = pdot(0.5, 0.5);//pdot(GWIDTH / 2, GHEIGHT / 2);
	player.plane = pdot(0, FOV);
	player.dir = pdot(-1, 0);
	player.z = 0;
	player.collision = 1;
	return (player);
}
