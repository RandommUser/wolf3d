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

static int	key_okay(int key)
{
	static int	keys[] = {
		ESC_KEY, L_CTRL, L_SHFT, K_W, K_A, K_S, K_D, K_AU, K_AR, K_AD, K_AL,
		K_Z, K_V, K_C, K_P, K_ENT, MOU_M, NO_KEY
	};
	int			i;

	i = -1;
	while (keys[++i] != NO_KEY)
		if (keys[i] == key)
			return (1);
	return (0);
}

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
	int	y;

	y = -1;
	while (--n >= 0)
	{
		if (tab[n] == NO_KEY && y > 0)
		{
			tab[n] = tab[y];
			tab[y] = NO_KEY;
		}
		if (tab[n] != NO_KEY)
			y = n;
	}
}

int			key_controls(int *tab, int n, int key, char ac)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	if (!key_okay(key))
		return (-1);
	while (++i < n && !ret)
	{
		if (ac == '-' && tab[i] == key)
		{
			tab[i] = NO_KEY;
			ret = 1;
		}
		else if (ac == '+' && tab[i] == NO_KEY)
		{
			tab[i] = key;
			ret = 1;
		}
		else if (ac == '+' && tab[i] == key)
			ret = -1;
	}
	order_tab(tab, n);
	return (ret);
}
