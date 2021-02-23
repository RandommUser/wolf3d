/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:14:00 by phakakos          #+#    #+#             */
/*   Updated: 2020/12/14 15:14:56 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	map_delete(t_map *map)
{
	if (!map)
		return ;
	free(map->name);
	map->name = NULL;
	free(map->desc);
	map->desc = NULL;
	free(map->next);
	map->next = NULL;
	free(map->version);
	map->version = NULL;
	block_tree_del(map->start);
	map->start = NULL;
	free(map->path);
	map->path = NULL;
}

t_map	map_empty(void)
{
	t_map	ret;

	ret.name = NULL;
	ret.desc = NULL;
	ret.next = NULL;
	ret.path = NULL;
	ret.size = dot(0, 0);
	ret.top = dot(0, 0);
	ret.bottom = dot(0, 0);
	ret.spawn = dot(0, 0);
	ret.start = NULL;
	ret.version = NULL;
	return (ret);
}
