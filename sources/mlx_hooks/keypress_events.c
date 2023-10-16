/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2023/10/16 06:35:05 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"

void	ft_destroy_window_button(int keysym, t_cub *data)
{
	if (keysym == XK_Escape)
	{
		mlx_loop_end(data->mlx_ptr);
		// mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		// data->win_ptr = NULL;
	}
}

/* Events catching movements and moving into the fractal window*/
void	ft_movements_keys(int keysym, t_cub *data, int state)
{
	int	i;

	i = 0;
	while (g_key_to_action[i].key_id != -1)
	{
		if (g_key_to_action[i].key_id == keysym)
		{
			data->inputs.action_states[g_key_to_action[i].action] = state;
			break ;
		}
		++i;
	}
}
