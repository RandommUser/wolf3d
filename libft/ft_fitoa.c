/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:29:24 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/10 15:29:25 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	*fail_safe(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

char		*ft_fitoa(double val, int prec)
{
	double	deci;
	char	*ret;
	char	*temp;
	char	*temp1;

	if (prec <= 0)
		return (ft_itoa_base(val, 10));
	deci = ((double)val - (long)val) * ft_pow(10, prec);
	deci += deci - (long)deci > 0.99 ? 1 : 0;
	if (!(temp = ft_itoa_base((long)val, 10)))
		return (NULL);
	if (!(temp1 = ft_strjoin(temp, DECIMAL_SPLIT)))
		return (fail_safe(temp));
	free(temp);
	if (!(temp = ft_itoa_base((long)deci, 10)))
		return (fail_safe(temp1));
	ret = ft_strjoin(temp1, temp);
	free(temp);
	free(temp1);
	return (ret);
}
