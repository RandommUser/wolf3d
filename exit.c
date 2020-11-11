/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:54:14 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/11 13:54:15 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	good_exit(int code, char *msg)
{
	if (msg)
		ft_putendl(msg);
	if (code == USAGE)
	{
		//usage here
	}
	exit(EXIT_SUCCESS);
}

void	err_exit(int error, char *msg)
{
	if (msg)
		ft_putendl(msg);
	exit(error);
}
