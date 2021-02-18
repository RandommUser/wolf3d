/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:26:46 by phakakos          #+#    #+#             */
/*   Updated: 2021/02/18 12:26:47 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*moved_str(char *str, char *cmp)
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

static int	map_header2(int ret, char *name, int fd, t_map *map)
{
	char	*line;
	char	*start;

	ret = ret == 1 ? get_next_line(fd, &line) : ret;
	if (ret == 1 && line && !(start = moved_str(line, MAP_NEXT)))
		ret = 0;
	if (ret == 1 && start && !(map->next = ft_strdup(start)))
		err_exit(ERR_MEMORY, "map_header next alloc");
	ft_memdel((void*)&line);
	if (ft_strrclen(name, '/') && !(map->path = ft_strsub(name, 0,
		ft_strrclen(name, '/') + 1)))
		err_exit(ERR_MEMORY, "map_header path alloc");
	return (ret == 1 ? 1 : 0);
}

int			map_header(char *name, int fd, t_map *map)
{
	char	*line;
	char	*start;
	int		ret;

	ret = get_next_line(fd, &line);
	if (ret == 1 && ft_strcmp(line, MAP_V))
		ret = 0;
	ft_memdel((void*)&line);
	ret = ret == 1 ? get_next_line(fd, &line) : ret;
	if (ret == 1 && line && !(start = moved_str(line, MAP_NAME)))
		ret = 0;
	if (ret == 1 && start && !(map->name = ft_strdup(start)))
		err_exit(ERR_MEMORY, "map_header name alloc");
	ft_memdel((void*)&line);
	ret = ret == 1 ? get_next_line(fd, &line) : ret;
	if (ret == 1 && line && !(start = moved_str(line, MAP_DESC)))
		ret = 0;
	if (ret && start && !(map->desc = ft_strdup(start)))
		err_exit(ERR_MEMORY, "map_header desc alloc");
	ft_memdel((void*)&line);
	return (map_header2(ret, name, fd, map));
}
