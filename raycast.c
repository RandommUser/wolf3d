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

void	traycast(t_ray ray)
{
	/*
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
	t_ray	ray;

	ray.game = game;
	ray.x = -1;
	while (++ray.x < game.mlx.size.x)
	{
		//printf("raycast %d\n", x);
		ray.camera = pmap(ray.x, nmap(0, game.mlx.size.x, -1, 1)); //2 * x / game.mlx.size.x - 1;
		ray.raydir.x = game.player.dir.x + game.player.plane.x * ray.camera;
		ray.raydir.y = game.player.dir.y + game.player.plane.y * ray.camera;
		ray.hit = 0;
		ray.dist.x = !ray.raydir.x ? 1 : ft_fabs(1 / ray.raydir.x); // DOES NOT LIKE 0?
		ray.dist.x = !ray.raydir.y ? 0 : ray.dist.x;
		ray.dist.y = !ray.raydir.y ? 1 : ft_fabs(1 / ray.raydir.y);
		ray.dist.y = !ray.raydir.x ? 0 : ray.dist.y;
		ray.map.x = dround(game.player.pos.x);
		ray.map.y = dround(game.player.pos.y);
		//printf("camera %f | ray %f %f | dist %f %f\n", camera, raydir.x, raydir.y, dist.x, dist.y);
		if (ray.raydir.x < 0)
		{
			ray.step.x = -1;
			ray.sdist.x = (game.player.pos.x - ray.map.x) * ray.dist.x;
		}
		else
		{
			ray.step.x = 1;
			ray.sdist.x = (ray.map.x + 1 - game.player.pos.x) * ray.dist.x;
		}
		if (ray.raydir.y < 0)
		{
			ray.step.y = -1;
			ray.sdist.y = (game.player.pos.y - ray.map.y) * ray.dist.y;
 		}
		else
		{
			ray.step.y = 1;
			ray.sdist.y = (ray.map.y + 1 - game.player.pos.y) * ray.dist.y;
		}
		ray.len = -1;
		//printf("finding wall\n");
		while (!ray.hit && ++ray.len < RDIST)
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
			ray.hit = is_transparent(game.map.start, ray.map);
			if (is_wall(game.map.start, ray.map))
				break ;
		}
		if (!hit)
			continue ;*/
		ray.block = find_spot(ray.game.map.start, ray.map);
		ray.wdist = !ray.side ? (ray.map.x - ray.game.player.pos.x + (1 - ray.step.x) / 2) / ray.raydir.x :
		(ray.map.y - ray.game.player.pos.y + (1 - ray.step.y) / 2) / ray.raydir.y;

		ray.lheight = ray.game.mlx.size.y / ray.wdist;

		ray.draw.x = -(ray.lheight) / 2 + ray.game.mid;
		//ray.draw.x = ray.draw.x < 0 ? 0 : ray.draw.x; // not needed
		ray.draw.y = ray.lheight / 2 + ray.game.mid;
		//ray.draw.y = ray.draw.y >= ray.game.mlx.size.y ? ray.game.mlx.size.y - 1 : ray.draw.y; // not needed

		if (ray.block->block == 7)
		{
			ray.color = 0xffffff;
			ray.draw.x = ray.draw.y - (ray.draw.y - ray.draw.x) / 10;
		}
		mlx_line_to_image(ray.game.image[1], dot(ray.x, ray.draw.x), dot(ray.x, ray.draw.y), ray.color);
	//}
}


void	raycast(t_game game)
{
	/*
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
	t_dot		draw;*/
	t_ray	ray;

	ray.game = game;
	ray.x = -1;
	if (game.verbose)
		printf("raycast start\n");
	while (++ray.x < game.mlx.size.x)
	{
		//printf("raycast %d\n", x);
		ray.camera = pmap(ray.x, nmap(0, game.mlx.size.x, -1, 1)); //2 * x / game.mlx.size.x - 1;
		ray.raydir.x = game.player.dir.x + game.player.plane.x * ray.camera;
		ray.raydir.y = game.player.dir.y + game.player.plane.y * ray.camera;
		ray.hit = 0;
		ray.dist.x = !ray.raydir.x ? 1 : ft_fabs(1 / ray.raydir.x); // DOES NOT LIKE 0?
		ray.dist.x = !ray.raydir.y ? 0 : ray.dist.x;
		ray.dist.y = !ray.raydir.y ? 1 : ft_fabs(1 / ray.raydir.y);
		ray.dist.y = !ray.raydir.x ? 0 : ray.dist.y;
		ray.map.x = dround(game.player.pos.x);
		ray.map.y = dround(game.player.pos.y);
		//printf("camera %f | ray %f %f | dist %f %f\n", camera, raydir.x, raydir.y, dist.x, dist.y);
		if (ray.raydir.x < 0)
		{
			ray.step.x = -1;
			ray.sdist.x = (game.player.pos.x - ray.map.x) * ray.dist.x;
		}
		else
		{
			ray.step.x = 1;
			ray.sdist.x = (ray.map.x + 1 - game.player.pos.x) * ray.dist.x;
		}
		if (ray.raydir.y < 0)
		{
			ray.step.y = -1;
			ray.sdist.y = (game.player.pos.y - ray.map.y) * ray.dist.y;
 		}
		else
		{
			ray.step.y = 1;
			ray.sdist.y = (ray.map.y + 1 - game.player.pos.y) * ray.dist.y;
		}
		ray.len = -1;
		//printf("finding wall\n");
		while (!ray.hit && ++ray.len < RDIST)
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
			//block = find_spot(game.map.start, map);
			//if (block)// && (block->block == 1 || block->block == 2 || block->block == 4 || block->block == 3)) // ADD MORE WALL CHECKS
			ray.block = find_spot(game.map.start, ray.map);
				if (is_transparent(NULL, ray.block, ray.map))
					traycast(ray);
				else
					ray.hit = is_wall(NULL, ray.block, ray.map);
			//block = hit ? block : NULL;
		}
	//	ray.block = find_spot(game.map.start, ray.map);
		//printf("wall found %d\n", len);
		ray.wdist = !ray.side ? (ray.map.x - game.player.pos.x + (1 - ray.step.x) / 2) / ray.raydir.x :
		(ray.map.y - game.player.pos.y + (1 - ray.step.y) / 2) / ray.raydir.y;

		ray.lheight = game.mlx.size.y / ray.wdist;

		ray.draw.x = -(ray.lheight) / 2 + game.mid;
		ray.draw.x = ray.draw.x < 0 ? 0 : ray.draw.x; // not needed
		ray.draw.y = ray.lheight / 2 + game.mid;
		ray.draw.y = ray.draw.y >= game.mlx.size.y ? game.mlx.size.y - 1 : ray.draw.y; // not needed
		// ADD COLOR CHANGES HERE
		//
		//color = side ? 0xff800 : 0xd412e1;
		if (ray.side)
			ray.color = ray.map.y > game.player.pos.y ? 0xff0000 : 0x0000ff;
		else
			ray.color = ray.map.x > game.player.pos.x ? 0xff8000 : 0x00ff00;
		if (ray.hit && ray.block->block == 7)
		{
			ray.color = 0xffffff;
			ray.draw.x = ray.draw.y - (ray.draw.y - ray.draw.x) / 10;
		}
		ray.color = !ray.hit ? 0x333333 : ray.color;
		//printf("sdist %f %f | map %d %d | wdist %f | lhei %d | draw %d %d\n",
		//	sdist.x, sdist.y, map.x, map.y, wdist, lheight, draw.x, draw.y);
		/*
		if (block)
		{
			color = block->block == 2 ? 0x333333 : color;
			color = block->block == 3 ? 0xff0000 : color;
			color = block->block == 4 ? 0x00ff00 : color;
		}
		*/
		//printf("drawing line from %d %d to %d %d\n", x , draw.x, x, draw.y);
		mlx_line_to_image(game.image[0], dot(ray.x, ray.draw.x), dot(ray.x, ray.draw.y), ray.color);
	}
}
