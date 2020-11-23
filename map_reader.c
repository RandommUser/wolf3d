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

static int	bad_map(int fd, t_editor *edit)
{
	close(fd);
	free(edit->name);
	free(edit->desc);
	free(edit->next);
	edit->name = NULL;
	edit->desc = NULL;
	edit->next = NULL;
	block_tree_del(edit->start);
	return (0);
}

static void	block_norm(t_editor *edit, t_mapb *start)
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
			spawn = dot(curr->base_s.x, curr->base_s.y);
		}
		limit.x = limit.x < curr->base_s.x ? curr->base_s.x : limit.x; // EMPTY NOT ADDED TO THE LIST
		limit.y = limit.y < curr->base_s.y ? curr->base_s.y : limit.y;
		curr = curr->next;
	}
	if (!found)
	{
		spawn = dot(iround(limit.x / 2), iround(limit.y / 2));
		printf("no spawn found\n");
	}
	edit->map_size.x = iround(limit.x / 2) < MAP_SIZE ? MAP_SIZE : iround(limit.x / 2);
	edit->map_size.y = iround(limit.y / 2) < MAP_SIZE ? MAP_SIZE : iround(limit.y / 2);
	printf("spawn is at %d %d\nmap size %d %d\n", spawn.x, spawn.y, limit.x, limit.y);
	curr = start;
	while (curr)
	{
	//	printf("base %d %d", curr->base_s.x, curr->base_s.y);
		curr->base_s.x -= spawn.x;
		curr->base_s.y -= spawn.y;
	//	printf(" normed %d %d\n", curr->base_s.x, curr->base_s.y);
		curr = curr->next;
	}
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

static int	block_read(int fd, t_editor *edit)
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
			if (!edit->start)
				edit->start = block_add(edit, ft_atoi(block), spot, block_param(&line[spot.x + pad]));
			else
			{
				block_edit(edit, ft_atoi(block), spot, block_param(&line[spot.x + pad]));
				printf("block added %d %d\n", spot.x, spot.y);
			}
		}
		printf("line %d:'%s'\n", spot.y, line);
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

static int	map_header(int fd, t_editor *edit)
{
	char	*line;
	char	*start;
	int		ret;

	ret = get_next_line(fd, &line); // version
	if (ret == 1 && !ft_strcmp(line, MAP_VERSION)) // DOES NOT WORK
		ret = 0;
	ft_memdel((void*)&line);
	ret == 1 ? ret = get_next_line(fd, &line) : ret; // name
	if (ret == 1  && line && !(start = moved_str(line, MAP_NAME)))
		ret = 0;
	if (ret == 1  && start && !(edit->name = ft_strdup(start)))
		err_exit(ERR_MEMORY, "map_header name alloc");
	ft_memdel((void*)&line);
	ret == 1 ? ret = get_next_line(fd, &line) : ret; // desc
	if (ret == 1  && line && !(start = moved_str(line, MAP_DESC)))
		ret = 0;
	if (ret && start && !(edit->desc = ft_strdup(start)))
		err_exit(ERR_MEMORY, "map_header desc alloc");
	ft_memdel((void*)&line);
	ret == 1 ? ret = get_next_line(fd, &line) : ret; // end
	if (ret == 1  && line && !(start = moved_str(line, MAP_NEXT)))
		ret = 0;
	if (ret == 1  && start && !(edit->next = ft_strdup(start)))
		err_exit(ERR_MEMORY, "map_header next alloc");
	ft_memdel((void*)&line);
	return (ret == 1 ? 1 : 0);
}

int		map_reader(char *name, t_editor *edit)
{
	int	fd;

	if (!file_ending(name, MAP_ENDING) || (fd = open(name, O_RDONLY)) < 1) // MAP NAME TESTING
		return (0);
	if (!map_header(fd, edit))
		return (bad_map(fd, edit));
	printf("Name: %s\nDesc: %s\nNext: %s\n", edit->name, edit->desc, edit->next);
	block_tree_del(edit->start);
	edit->start = NULL;
	printf("old blocks wiped\n");
	edit->map_size = dot(0, 0);
	if (!block_read(fd, edit))
		return (bad_map(fd, edit));
	printf("blocks read\n");
	block_norm(edit, edit->start);
	//block_list(edit->start);
	// NORM THE COORDINATES
	close(fd);
	return (1);
}
