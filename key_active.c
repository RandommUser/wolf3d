/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_active.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:03:22 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/12 15:03:23 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		log_reset(int *tab, int n, int key)
{
	int	i;

	i = -1;
	while (++i < n)
		tab[i] = key;
}

int			is_pressed(int *tab, int n, int key)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (tab[i] == key)
			return (1);
	}
	return (0);
}

static void	order_tab(int *tab, int n)
{
	int	i;
	int	y;

	i = n;
	y = -1;
	while (--i >= 0)
	{
		if (tab[i] == NO_KEY && y > 0)
		{
			tab[i] = tab[y];
			tab[y] = NO_KEY;
		}
		if (tab[i] != NO_KEY)
			y = i;
	}
}

int			key_controls(int *tab, int n, int key, char ac)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	if (ac == '-')
	{
		while (++i < n && !ret)
			if (tab[i] == key)
			{
				tab[i] = NO_KEY;
				ret = 1;
			}
	}
	else if (ac == '+')
	{
		while (++i < n && !ret)
			if (tab[i] == NO_KEY)
			{
				tab[i] = key;
				ret = 1;
			}
			else if (tab[i] == key)
				ret = -1;
	}
	order_tab(tab, n);
	return (ret);
}
