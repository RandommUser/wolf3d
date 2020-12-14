/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:52:11 by phakakos          #+#    #+#             */
/*   Updated: 2020/12/14 15:52:12 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		mlx_pixel_place(t_mlx mlx, t_dot pos, int color)
{
	if (pos.x > mlx.size.x || pos.y > mlx.size.y)
		return (0);
	mlx_pixel_put(mlx.mlx_ptr, mlx.mlx_win, pos.x, pos.y, color);
	return (1);
}

int		mlx_image_place(t_mlx mlx, void *img_ptr, t_dot pos)
{
	if (pos.x > mlx.size.x || pos.y > mlx.size.y || !img_ptr)
		return (0);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.mlx_win, img_ptr, pos.x, pos.y);
	return (1);
}

void	t_mlx_delete(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx->mlx_ptr = NULL;
	mlx->mlx_win = NULL;
	mlx->size = dot(0, 0);
}

t_mlx	mlx_start(void *mlx_ptr, int width, int height, char *title)
{
	t_mlx	mlx;

	if (!(mlx.mlx_win = mlx_new_window(mlx_ptr, width, height, title)))
		err_exit(ERR_MLX, "mlx_start() new window");
	mlx.mlx_ptr = mlx_ptr;
	mlx.size = dot(width, height);
	return (mlx);
}
