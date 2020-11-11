/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:32:41 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/10 15:32:42 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_pow(double val, int power)
{
	double	ret;
	int		pow;

	if (!power)
		return (1);
	ret = val;
	pow = ft_abs(power);
	while (--pow > 0)
		ret *= val;
	if (power < 0)
		ret = 1 / ret;
	return (ret);
}
