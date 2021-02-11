/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_writer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:08:59 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/16 16:09:01 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*file_format(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (!ft_strcmp(&name[i], MAP_ENDING)) // ignore .map part at the end
			break ;
		name[i] = ft_iswspace(name[i]) ? '_' : name[i];
		name[i] = name[i] != '_' && !ft_isalnum(name[i]) ? '-' : name[i];
		name[i] = ft_isupper(name[i]) ? ft_tolower(name[i]) : name[i];
	}
	return (name);
}

static void	map_header(int fd, t_map *map)
{
	ft_putendl_fd(MAP_V, fd);
	ft_putstr_fd(MAP_NAME, fd);
	ft_putendl_fd(map->name, fd);
	ft_putstr_fd(MAP_DESC, fd);
	ft_putendl_fd(map->desc, fd);
	ft_putstr_fd(MAP_NEXT, fd);
	ft_putendl_fd(MAP_END, fd);
}

static void	map_loop(int fd, t_map *map)
{
	t_dot	pos;
	t_mapb	*block;

	pos.y = -map->size.y - 1;
	while (++pos.y <= map->size.y)
	{
		pos.x = -map->size.x - 1;
		while (++pos.x <= map->size.x)
		{
			if (!(block = find_spot(map->start, pos)) || !block->block)
				ft_putchar_fd(MAP_EMPTY, fd);
			else
			{
				ft_putnbr_fd(block->block, fd);
				if (block->param)
				{
					ft_putchar_fd(MAP_SPLIT, fd);
					ft_putstr_fd(block->param, fd);
					ft_putchar_fd(MAP_SPLIT_END, fd);
				}
			}
		}
		ft_putchar_fd('\n', fd);
	}
}


int	map_write(t_map *map)
{
	int		fd;
	char	*temp[2];

	if (!(temp[0] = ft_strdup(map->name)))
		err_exit(ERR_MEMORY, "map_write file name alloc");
	temp[0] = file_format(temp[0]);
	temp[1] = temp[0];
	printf("1\n");
	if (map->path && !(temp[0] = ft_strjoin(map->path, temp[1])))
		err_exit(ERR_MEMORY, "map_write file name alloc");
	if (temp[0] != temp[1])
		free(temp[1]);
	printf("2\n");
	if (!(temp[1] = ft_strjoin(temp[0], MAP_ENDING)))
		err_exit(ERR_MEMORY, "map_write file name alloc");
	free(temp[0]);
	printf("3\n");
	if ((fd = open(temp[1], O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
	{
		free(temp[1]);
		return (0);
	}
	free(temp[1]);
	printf("4\n");
	map_header(fd, map);
	map_loop(fd, map);
	close(fd);
	return (1);
}
