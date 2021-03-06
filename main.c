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
	if (argc > 1 && !ft_strcmp(argv[1], "editor"))
		argc > 2 ? editor(argv[2]) : editor(NULL);
	else if (argc == 2)
		game(argv[1]);
	else
		good_exit(USAGE, "Bad start parameters");
	return (0);
}
