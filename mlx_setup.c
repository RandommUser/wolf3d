/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:13:48 by phakakos          #+#    #+#             */
/*   Updated: 2021/02/18 12:13:49 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		t_mlx_delete(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx->mlx_ptr = NULL;
	mlx->mlx_win = NULL;
	mlx->size = dot(0, 0);
	return (1);
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
