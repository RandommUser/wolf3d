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

static int	bad_map(int fd, t_map *map)
{
	close(fd);
	map_delete(map);
	return (0);
}

static void	block_norm(t_map *map, t_mapb *start)
{
	int		found;
	t_dot	limit;
	t_dot	spawn;
	t_mapb	*curr;

	curr = start;
	limit = dot(0,0);
	found = 0;
	while (curr)
	{
		if(!found && block_check(curr, MAP_SPAWN_FLAG))
		{
			found = 1;
			spawn = curr->pos;
		}
		limit.x = limit.x < curr->pos.x ? curr->pos.x : limit.x; // EMPTY NOT ADDED TO THE LIST
		limit.y = limit.y < curr->pos.y ? curr->pos.y : limit.y;
		curr = curr->next;
	}
	if (!found)
	{
		spawn = dot(iround(limit.x / 2), iround(limit.y / 2));
		//printf("no spawn found\n");
	}
	map->size.x = iround(limit.x / 2) < MAP_SIZE ? MAP_SIZE : iround(limit.x / 2);
	map->size.y = iround(limit.y / 2) < MAP_SIZE ? MAP_SIZE : iround(limit.y / 2);
	//printf("spawn is at %d %d\nmap size %d %d\n", spawn.x, spawn.y, limit.x, limit.y);
	curr = start;
	while (curr)
	{
		curr->pos.x -= spawn.x;
		curr->pos.y -= spawn.y;
		curr = curr->next;
	}
	map->spawn = dot(0, 0); // = spawn if u remove the above while loop
}

static char	*block_param(char *line)
{
	int		i;
	char	*ret;

	if (line[1] != MAP_SPLIT)
		return (NULL);
	i = -1;
	while (line[++i])
		if (line[i] == MAP_SPLIT_END)
			break ;
	if (!(ret = ft_strsub(line, 2, i - 2)))
		err_exit(ERR_MEMORY, "block_param ret alloc");
	return (ret);
}

static int	block_read(int fd, t_map *map)
{
	t_dot	spot;
	int		pad;
	char	*line;
	char	block[2];

	spot.y = -1;
	block[1] = '\0';
	while (get_next_line(fd, &line) > 0)
	{
		spot.y++;
		spot.x = -1;
		pad = 0;
		while (line[++spot.x + pad])
		{
			if (line[spot.x + pad] == MAP_SPLIT)
			{
				while (line[spot.x + pad])
					if (line[spot.x + pad++] == MAP_SPLIT_END)
						break ;
				if (!line[spot.x + pad])
					return (0);
			}
			if (line[spot.x + pad] == MAP_EMPTY)
				block[0] = '0';
			else
				block[0] = line[spot.x + pad];
			if (!map->start)
				map->start = block_add(map, ft_atoi(block), spot, block_param(&line[spot.x + pad]));
			else
			{
				block_edit(map, ft_atoi(block), spot, block_param(&line[spot.x + pad]));
				//printf("block added %d %d\n", spot.x, spot.y);
			}
		}
		//printf("line %d:'%s'\n", spot.y, line);
		ft_memdel((void*)&line);
	}
	return (1);
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

static char *moved_str(char *str, char *cmp)
{
	int	i;

	i = -1;
	while (str[++i] && cmp[i])
	{
		if (str[i] != cmp[i])
			return (NULL);
	}
	return (&str[i]);
}

static int	map_header(char *name, int fd, t_map *map)
{
	char	*line;
	char	*start;
	int		ret;

	ret = get_next_line(fd, &line); // version
	if (ret == 1 && ft_strcmp(line, MAP_V))
	{
		printf("'%s' vs '%s'\n", line, MAP_V);
		ret = 0;
	}
	ft_memdel((void*)&line);
	ret = ret == 1 ? ret = get_next_line(fd, &line) : ret; // name
	if (ret == 1  && line && !(start = moved_str(line, MAP_NAME)))
		ret = 0;
	if (ret == 1  && start && !(map->name = ft_strdup(start)))
		err_exit(ERR_MEMORY, "map_header name alloc");
	ft_memdel((void*)&line);
	ret = ret == 1 ? ret = get_next_line(fd, &line) : ret; // desc
	if (ret == 1  && line && !(start = moved_str(line, MAP_DESC)))
		ret = 0;
	if (ret && start && !(map->desc = ft_strdup(start)))
		err_exit(ERR_MEMORY, "map_header desc alloc");
	ft_memdel((void*)&line);
	ret = ret == 1 ? ret = get_next_line(fd, &line) : ret; // end
	if (ret == 1  && line && !(start = moved_str(line, MAP_NEXT)))
		ret = 0;
	if (ret == 1  && start && !(map->next = ft_strdup(start)))
		err_exit(ERR_MEMORY, "map_header next alloc");
	ft_memdel((void*)&line);
	if (ft_strlen(name) != ft_strclen(name, '/'))
	{
		map->path = ft_strsub(name, 0, ft_strclen(name, '/') + 1);
	}
	return (ret == 1 ? 1 : 0);
}

int		map_reader(char *name, t_map *map)
{
	int	fd;

	if (!file_ending(name, MAP_ENDING) || (fd = open(name, O_RDONLY)) < 1) // MAP NAME TESTING
		return (0);
	if (!map_header(name, fd, map))
		return (bad_map(fd, map));
	printf("Name: %s\nDesc: %s\nNext: %s\n", map->name, map->desc, map->next);
	block_tree_del(map->start);
	map->start = NULL;
	printf("old blocks wiped\n");
	map->size = dot(0, 0);
	if (!block_read(fd, map))
		return (bad_map(fd, map));
	printf("blocks read\n");
	block_norm(map, map->start);
	//block_list(edit->start);
	// NORM THE COORDINATES
	close(fd);
	return (1);
}
