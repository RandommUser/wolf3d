/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:26:54 by phakakos          #+#    #+#             */
/*   Updated: 2021/02/18 12:26:55 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

static void	block_to_map(t_map *map, char *line, t_dot spot, int pad)
{
	char	block[2];

	block[1] = '\0';
	if (line[spot.x + pad] == MAP_EMPTY)
		block[0] = '0';
	else
		block[0] = line[spot.x + pad];
	if (!map->start)
		map->start = block_add(map, ft_atoi(block), spot,
			block_param(&line[spot.x + pad]));
	else
		block_edit(map, ft_atoi(block), spot,
			block_param(&line[spot.x + pad]));
}

int			block_read(int fd, t_map *map)
{
	t_dot	spot;
	int		pad;
	char	*line;

	spot.y = -1;
	while (get_next_line(fd, &line) > 0)
	{
		spot = dot(-1, spot.y + 1);
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
			block_to_map(map, line, spot, pad);
		}
		ft_memdel((void*)&line);
	}
	return (1);
}
