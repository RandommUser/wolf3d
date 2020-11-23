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
		/*
		name[i] = name[i] == '/' ? '-' : name[i];
		name[i] = name[i] == '\\' ? '-' : name[i];
		name[i] = name[i] == '"' ? '-' : name[i];
		name[i] = name[i] == '\'' ? '-' : name[i];
		name[i] = name[i] == '`' ? '-' : name[i];
		name[i] = name[i] == '!' ? '-' : name[i];
		name[i] = name[i] == '@' ? '-' : name[i];
		name[i] = name[i] == '#' ? '-' : name[i];
		name[i] = name[i] == '$' ? '-' : name[i];
		name[i] = name[i] == '%' ? '-' : name[i];
		name[i] = name[i] == '^' ? '-' : name[i];
		name[i] = name[i] == '&' ? '-' : name[i];
		name[i] = name[i] == '*' ? '-' : name[i];
		name[i] = name[i] == ',' ? '-' : name[i];
		name[i] = name[i] == ':' ? '-' : name[i];
		name[i] = name[i] == ';' ? '-' : name[i];
		*/
	}
	return (name);
}

static void	map_header(FILE *fd, t_editor *edit)
{
	fprintf(fd, "%s\n", MAP_V);
	fprintf(fd, "%s%s\n", MAP_NAME, edit->name);
	fprintf(fd, "%s%s\n", MAP_DESC, edit->desc);
	fprintf(fd, "%s%s\n", MAP_NEXT, MAP_END); // ADD A FEATURE TO CONNECT MAPS LATER
}

static void	map_loop(FILE *fd, t_editor *edit)
{
	t_dot	map;
	t_mapb	*block;

	map.y = -edit->map_size.y - 1;
	while (++map.y <= edit->map_size.y)
	{
		map.x = -edit->map_size.x - 1;
		while (++map.x <= edit->map_size.x)
		{
			if (!(block = find_spot(edit->start, map)) || !block->block)
				fprintf(fd, "%c", MAP_EMPTY);
			else
			{
				fprintf(fd, "%d", block->block);
				if (block->param)
					fprintf(fd, "%c%s%c", MAP_SPLIT, block->param, MAP_SPLIT_END);
			}
		}
		fprintf(fd, "\n");
	}
}


int	map_write(t_editor *edit)
{
	FILE	*fd;
	char	*temp;

	if (!(temp = ft_strjoin(edit->name, MAP_ENDING)))
		err_exit(ERR_MEMORY, "map_write file name alloc");
	temp = file_format(temp);
	if (!(fd = fopen(temp, "w")))
	{
		free(temp);
		return (0);
	}
	free(temp);
	map_header(fd, edit);
	map_loop(fd, edit);
	fclose(fd);
	return (1);
}
