/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:12:13 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/20 14:12:14 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	block_norm2(t_map *map, t_dot limit, t_dot spawn, int found)
{
	t_mapb	*curr;

	if (!found)
		spawn = dot(iround(limit.x / 2), iround(limit.y / 2));
	map->size.x = iround(limit.x / 2) < MAP_SIZE ? MAP_SIZE :
		iround(limit.x / 2);
	map->size.y = iround(limit.y / 2) < MAP_SIZE ? MAP_SIZE :
		iround(limit.y / 2);
	map->top = dot(-spawn.x, -spawn.y);
	map->bottom = dot(limit.x - spawn.x, limit.y - spawn.y);
	curr = map->start;
	while (curr)
	{
		curr->pos.x -= spawn.x;
		curr->pos.y -= spawn.y;
		curr = curr->next;
	}
	map->spawn = dot(0, 0);
}

static void	block_norm(t_map *map)
{
	int		found;
	t_dot	limit;
	t_dot	spawn;
	t_mapb	*curr;

	curr = map->start;
	limit = dot(0, 0);
	found = 0;
	while (curr)
	{
		if (!found && block_check(curr, MAP_SPAWN_FLAG) &&
			!is_wall(NULL, curr, dot(0, 0)))
		{
			found = 1;
			spawn = curr->pos;
		}
		limit.x = limit.x < curr->pos.x ? curr->pos.x : limit.x;
		limit.y = limit.y < curr->pos.y ? curr->pos.y : limit.y;
		curr = curr->next;
	}
	block_norm2(map, limit, spawn, found);
}

static int	bad_map(int fd, t_map *map)
{
	close(fd);
	map_delete(map);
	return (0);
}

static int	file_ending(char *str, char *end)
{
	int	i;
	int	y;

	i = ft_strlen(str);
	y = ft_strlen(end);
	while (--i >= 0 && --y >= 0)
	{
		if (str[i] != end[y])
			return (0);
	}
	return (1);
}

int			map_reader(char *name, t_map *map)
{
	int	fd;

	if (!file_ending(name, MAP_ENDING) || (fd = open(name, O_RDONLY)) < 1)
		return (0);
	if (!map_header(name, fd, map))
		return (bad_map(fd, map));
	block_tree_del(map->start);
	map->start = NULL;
	map->size = dot(0, 0);
	if (!block_read(fd, map))
		return (bad_map(fd, map));
	block_norm(map);
	if (!map_valid(map))
		return (bad_map(fd, map));
	close(fd);
	return (1);
}
