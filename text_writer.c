/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_writer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:02:44 by phakakos          #+#    #+#             */
/*   Updated: 2020/11/25 14:02:45 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	in_screen(t_dot pos, t_dot size, char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (ft_iswspace(str[i]))
			break ;
		else if (str[i] == '-')
		{
			i++;
			break ;
		}
	pos.x += TEXT_WIDTH * (i + 1);
	return (pos.x < size.x);
}

static t_print	print_split(t_print print, int *prog, int *i)
{
	char	*temp;

	if (!(temp = ft_strsub(print.str, 0, *i)))
		err_exit(ERR_MEMORY, "write_to_screen temp alloc"); // error exit
	if (print.str[*i - 1] == '-')
		*i = *i - 1;
	mlx_string_put(print.mlx.mlx_ptr, print.mlx.mlx_win, *prog - *i * TEXT_WIDTH,
		print.pos.y, print.color, temp);
	print.str = &print.str[++*i];
	if (print.str[-1] == '\n')
		print.pos.y += TEXT_HEIGHT;
	if (print.str[-1] == '\t')
	{
		*prog += TEXT_WIDTH * 4;
		if (!in_screen(dot(*prog, print.pos.y), print.mlx.size, print.str)) // test if wrapping after tab is needed
		{
			*prog = print.pos.x;
			print.pos.y += TEXT_HEIGHT;
		}
	}
	else
		*prog = print.pos.x;
	free(temp);
	*i = -1;
	return (print);
}

void	write_screen(t_print print)
{
	int		i;
	int		prog;

	i = -1;
	print.pos = dot(print.pos.x - 2, print.pos.y - 4); // offset correction;
	prog = print.pos.x;
	while (print.str[++i] && print.pos.y < print.mlx.size.y)
	{
		if (print.str[i] == '\n' || print.str[i] == '\t') // encounters a linebreak or tabulations
			print = print_split(print, &prog, &i);
		else if ((ft_iswspace(print.str[i]) || (print.str[i] == '-')) &&
		!in_screen(dot(prog, print.pos.y), print.mlx.size, &print.str[i + 1]))// encounters any other kind of white-space or - and wrapping is needed
		{
			if (print.str[i] == '-')
			{
				i++;
				print = print_split(print, &prog, &i);
			}
			else
				print = print_split(print, &prog, &i);
			print.pos.y += TEXT_HEIGHT;
		}
		prog += i == -1 ? 0 : TEXT_WIDTH;
	}
	print_split(print, &prog, &i);
}

void	write_to_screen(t_mlx mlx, t_dot pos, int color, char *str)
{
	t_print print;

	print.mlx = mlx;
	print.pos = pos;
	print.str = str;
	print.color = color;
	write_screen(print);
}
