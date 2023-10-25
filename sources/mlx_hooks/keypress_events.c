/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2023/10/10 19:28:18 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"

void	ft_destroy_window_button(int keysym, t_cub *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
}

/* Events catching movements and moving into the fractal window*/
void	ft_movements_keys(int keysym, t_cub *data)
{
	if (data->update)
		return ;
	if (keysym == W_KEY)
		printf("W_KEY pressed\n");
	else if (keysym == S_KEY)
		printf("W_KEY pressed\n");
	else if (keysym == A_KEY)
		printf("W_KEY pressed\n");
	else if (keysym == D_KEY)
		printf("W_KEY pressed\n");
	else if (keysym == LEFT_KEY)
		printf("W_KEY pressed\n");
	else if (keysym == RIGHT_KEY)
		printf("W_KEY pressed\n");
	data->update = 1;
}
