/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:58:44 by phakakos          #+#    #+#             */
/*   Updated: 2020/12/18 11:58:46 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	raycast(t_game game)
{
	int			x;
	int			len;
	int			side;
	int			hit;
	int			lheight;
	int			color;
	PRECISION	camera;
	PRECISION	wdist;
	t_mapb		*block;
	t_pdot		raydir;
	t_pdot		dist;
	t_pdot		sdist;
	t_dot		map;
	t_dot		step;
	t_dot		draw;

	x = -1;
	printf("raycast start\n");
	while (++x < game.mlx.size.x)
	{
		//printf("raycast %d\n", x);
		camera = 2 * x / game.mlx.size.x - 1;
		raydir.x = game.player.dir.x + game.player.plane.x * camera;
		raydir.y = game.player.dir.y + game.player.plane.y * camera;
		hit = 0;
		dist.x = ft_fabs(1 / raydir.x); // DOES NOT LIKE 0
		dist.y = ft_fabs(1 / raydir.y);
		map.x = game.player.pos.x;
		map.y = game.player.pos.y;
		if (raydir.x < 0)
		{
			step.x = -1;
			sdist.x = (game.player.pos.x - map.x) * dist.x;
		}
		else
		{
			step.x = 1;
			sdist.x = (map.x + 1 - game.player.pos.x) * dist.x;
		}
		if (raydir.y < 0)
		{
			step.y = -1;
			sdist.y = (game.player.pos.y - map.y) * dist.y;
 		}
		else
		{
			step.y = 1;
			sdist.y = (map.y + 1 - game.player.pos.y) * dist.y;
		}
		len = -1;
		//printf("finding wall\n");
		while (!hit && ++len < RDIST)
		{
			if (sdist.x < sdist.y)
			{
				sdist.x += dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				sdist.y += dist.y;
				map.y += step.y;
				side = 1;
			}
			block = find_spot(game.map.start, map);
			if (block && (block->block == 1 || block->block == 2 || block->block == 4)) // ADD MORE WALL CHECKS
				hit = 1;
		}
		//printf("wall found %d\n", len);
		wdist = !side ? (map.x - game.player.pos.x + (1 - step.x) / 2) / raydir.x : 0;
		wdist = side ? (map.y - game.player.pos.y + (1 - step.y) / 2) / raydir.y : wdist;
		lheight = game.mlx.size.y / wdist;
		draw.x = -lheight / 2 + game.mlx.size.y / 2;
		draw.x = draw.x < 0 ? 0 : draw.x;
		draw.y = lheight / 2 + game.mlx.size.y / 2;
		draw.y = draw.y >= game.mlx.size.y ? game.mlx.size.y - 1 : draw.y;
		// ADD COLOR CHANGES HERE
		// drawline(draw.x, draw.y, 0xff0000);
		color = 0xff0000;
		if (block)
		{
			color = block->block == 2 ? 0x00ff00 : color;
			color = block->block == 4 ? 0x0000ff : color;
		}
		//printf("drawing line from %d %d to %d %d\n", x , draw.x, x, draw.y);
		mlx_line_to_image(game.image, dot(x, draw.x), dot(x, draw.y), color);
	}
}
