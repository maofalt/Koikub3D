/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:44:33 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/14 23:51:55 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"

void	ft_mlx_engine(t_cub *data)
{
	mlx_hook(data->win_ptr, ButtonPress, ButtonPressMask,
		&ft_handle_boutonpress, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &ft_handle_keypress, data);
	mlx_hook(data->win_ptr, 17, 0L, &ft_destroy_window, data);
	mlx_key_hook(data->win_ptr, &ft_handle_keyrelease, data);
	//mlx_hook(data->win_ptr, 6, (1L << 6), &ft_handle_mouse, data);
	mlx_loop(data->mlx_ptr);
}
