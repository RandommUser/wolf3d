/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:16:30 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/09 13:16:53 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv)
{
	int	texture[10 * 10];
	int	size = 10;
	t_dot	tsize;

	if (argc == 2 && !ft_strcmp(argv[1], "editor"))
		editor();
	printf("%s\n", MAP_V);
	tsize.x = size;
	tsize.y = size;
//	spawn_color(texture, tsize, SPAWN_1, SPAWN_2);
//	printf("block0h = %d\nblock0s = %d\n", BLOCK0H, BLOCK0S);
	wall_color(texture, tsize, WALL_1, WALL_2);
	outline_color(texture, tsize, BAR_SELECTC, -1);
	int i = -1;
	while (++i < size * size)
	{
		if (i && !(i % size))
			printf("\n");
		printf("0x%X, ", texture[i]);
	}
	printf("\n");
	return (0);
}
