/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:50:01 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/17 12:50:28 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strrclen(const char *s, char c)
{
	size_t	i;
	char	*ss;

	if (!s || !s[0])
		return (0);
	i = ft_strlen(s) - 1;
	ss = (char*)s;
	while (ss[i] && ss[i] != c)
		i--;
	return (i);
}

size_t	ft_strclen(const char *s, char c)
{
	long	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i += 1;
	}
	return (i);
}
