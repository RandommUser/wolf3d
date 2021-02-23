/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:07:19 by phakakos          #+#    #+#             */
/*   Updated: 2021/02/18 12:07:22 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_ray	ray_text(t_ray ray)
{
	t_precision	hit;

	if (ray.side)
		ray.tside = ray.map.y > ray.game.player.pos.y ? 0 : 1;
	else
		ray.tside = ray.map.x > ray.game.player.pos.x ? 2 : 3;
	if (!ray.side)
		hit = ray.game.player.pos.y + ray.wdist * ray.raydir.y;
	else
		hit = ray.game.player.pos.x + ray.wdist * ray.raydir.x;
	hit = ft_fabs(hit);
	hit = hit - (int)hit;
	hit = !ray.side && ray.block && ray.block->pos.y < 0 ? 1 - hit : hit;
	hit = ray.side && ray.block && ray.block->pos.x < 0 ? 1 - hit : hit;
	hit = hit > 1 ? 1 : hit;
	if (ray.block && ray.block->block < 5)
	{
		ray.color[0] = ray.game.text[ray.tside][iround(hit)];
		ray.color[1] = ray.game.text[ray.tside][iround(hit) + 2];
	}
	return (ray);
}

t_ray			ray_colors(t_ray ray)
{
	if (ray.hit)
		ray = ray_text(ray);
	else
	{
		ray.color[0] = !ray.hit ? 0x333333 : ray.color[0];
		ray.color[1] = !ray.hit ? 0x333333 : ray.color[1];
	}
	if (ray.block && ray.block->block == 7)
	{
		ray.color[0] = 0xffffff;
		ray.draw.x = ray.draw.y - (ray.draw.y - ray.draw.x) / 10;
	}
	return (ray);
}

static t_ray	ray_dir(t_ray ray)
{
	if (ray.raydir.x < 0)
	{
		ray.step.x = -1;
		ray.sdist.x = (ray.game.player.pos.x - ray.map.x) * ray.dist.x;
	}
	else
	{
		ray.step.x = 1;
		ray.sdist.x = (ray.map.x + 1 - ray.game.player.pos.x) * ray.dist.x;
	}
	if (ray.raydir.y < 0)
	{
		ray.step.y = -1;
		ray.sdist.y = (ray.game.player.pos.y - ray.map.y) * ray.dist.y;
	}
	else
	{
		ray.step.y = 1;
		ray.sdist.y = (ray.map.y + 1 - ray.game.player.pos.y) * ray.dist.y;
	}
	ray.len = -1;
	return (ray);
}

t_ray			ray_setup(t_game game, t_ray ray)
{
	ray.camera = pmap(ray.x, nmap(0, game.mlx.size.x, -1, 1));
	ray.raydir.x = game.player.dir.x + game.player.plane.x * ray.camera;
	ray.raydir.y = game.player.dir.y + game.player.plane.y * ray.camera;
	ray.hit = 0;
	ray.dist.x = !ray.raydir.x ? 1 : ft_fabs(1 / ray.raydir.x);
	ray.dist.x = !ray.raydir.y ? 0 : ray.dist.x;
	ray.dist.y = !ray.raydir.y ? 1 : ft_fabs(1 / ray.raydir.y);
	ray.dist.y = !ray.raydir.x ? 0 : ray.dist.y;
	ray.map.x = dround(game.player.pos.x);
	ray.map.y = dround(game.player.pos.y);
	ray.side = 0;
	return (ray_dir(ray));
}
