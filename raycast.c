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

t_ray	ray_bsize(t_ray ray)
{
	ray.wdist = !ray.side ? (ray.map.x - ray.game.player.pos.x +
		(1 - ray.step.x) / 2) / ray.raydir.x : (ray.map.y -
		ray.game.player.pos.y + (1 - ray.step.y) / 2) / ray.raydir.y;
	ray.lheight = ray.game.mlx.size.y / ray.wdist;
	ray.draw.x = -(ray.lheight) / 2 + ray.game.player.look;
	ray.draw.y = ray.lheight / 2 + ray.game.player.look;
	return (ray);
}

t_ray	ray_move(t_ray ray)
{
	if (ray.sdist.x < ray.sdist.y)
	{
		ray.sdist.x += ray.dist.x;
		ray.map.x += ray.step.x;
		ray.side = 0;
	}
	else
	{
		ray.sdist.y += ray.dist.y;
		ray.map.y += ray.step.y;
		ray.side = 1;
	}
	return (ray);
}

void	traycast(t_ray ray)
{
	ray = ray_bsize(ray);
	ray = ray_colors(ray);
	mlx_line_to_image(ray.game.image[1], dot(ray.x, ray.draw.x),
		dot(ray.x, ray.draw.y), ray.color[0]);
	ray = ray_move(ray);
	ray = ray_bsize(ray);
	ray = ray_colors(ray);
	mlx_line_to_image(ray.game.image[1], dot(ray.x, ray.draw.x),
		dot(ray.x, ray.draw.y), ray.color[0]);
}

void	raycast(t_game game)
{
	t_ray	ray;

	ray.game = game;
	ray.game.player.look += game.mlx.size.y / 2;
	ray.x = -1;
	while (++ray.x < game.mlx.size.x)
	{
		ray = ray_setup(game, ray);
		while (!ray.hit && ++ray.len < RDIST)
		{
			ray.block = find_spot(game.map.start, ray.map);
			if (is_transparent(NULL, ray.block, ray.map))
				traycast(ray);
			else
				ray.hit = is_wall(NULL, ray.block, ray.map);
			ray = !ray.hit || !ray.len ? ray_move(ray) : ray;
		}
		ray = ray_bsize(ray);
		ray.draw.x = ray.draw.x < 0 ? 0 : ray.draw.x;
		ray = ray_colors(ray);
		mlx_line_to_image(game.image[0], dot(ray.x, ray.draw.x),
			dot(ray.x, ray.game.player.look), ray.color[0]);
		mlx_line_to_image(game.image[0], dot(ray.x, ray.game.player.look - 1),
			dot(ray.x, ray.draw.y), ray.color[1]);
	}
}
