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

t_ray	ray_colors(t_ray ray)
{
	if (ray.side)
		ray.color = ray.map.y > ray.game.player.pos.y ? 0xff0000 : 0x0000ff;
	else
		ray.color = ray.map.x > ray.game.player.pos.x ? 0xff8000 : 0x00ff00;
	if (ray.hit && ray.block->block == 7)
	{
		ray.color = 0xffffff;
		ray.draw.x = ray.draw.y - (ray.draw.y - ray.draw.x) / 10;
	}
	ray.color = !ray.hit ? 0x333333 : ray.color;
	if (ray.block && ray.block->block == 7)
	{
		ray.color = 0xffffff;
		ray.draw.x = ray.draw.y - (ray.draw.y - ray.draw.x) / 10;
	}
	return (ray);
}

t_ray	ray_dir(t_ray ray)
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

t_ray	ray_setup(t_game game, t_ray ray)
{
	ray.camera = pmap(ray.x, nmap(0, game.mlx.size.x, -1, 1));
	ray.raydir.x = game.player.dir.x + game.player.plane.x * ray.camera;
	ray.raydir.y = game.player.dir.y + game.player.plane.y * ray.camera;
	ray.hit = 0;
	ray.dist.x = !ray.raydir.x ? 1 : ft_fabs(1 / ray.raydir.x); // DOES NOT LIKE 0?
	ray.dist.x = !ray.raydir.y ? 0 : ray.dist.x;
	ray.dist.y = !ray.raydir.y ? 1 : ft_fabs(1 / ray.raydir.y);
	ray.dist.y = !ray.raydir.x ? 0 : ray.dist.y;
	ray.map.x = dround(game.player.pos.x);
	ray.map.y = dround(game.player.pos.y);
	ray.side = 0;
	return (ray_dir(ray));
}

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
		dot(ray.x, ray.draw.y), ray.color);
	// secondary border calc to show the other side
	ray = ray_move(ray);
	ray = ray_bsize(ray);
	ray = ray_colors(ray);
	mlx_line_to_image(ray.game.image[1], dot(ray.x, ray.draw.x),
		dot(ray.x, ray.draw.y), ray.color);
}


void	raycast(t_game game)
{
	t_ray	ray;

	ray.game = game;
	ray.game.player.look += game.mlx.size.y / 2;
	ray.x = -1;
	if (game.verbose)		//
		printf("raycast start\n");		//
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
		if (ray.game.verbose)		//
			printf("x: %d wall found %d\n", ray.x, ray.len);		//
		ray = ray_bsize(ray);
		ray.draw.x = ray.draw.x < 0 ? 0 : ray.draw.x;
		ray = ray_colors(ray);
		if (ray.game.verbose)		//
			printf("drawing line from y %d to %d\n", ray.draw.x, ray.draw.y);		//
		mlx_line_to_image(game.image[0], dot(ray.x, ray.draw.x),
			dot(ray.x, ray.draw.y), ray.color);
	}
}
