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

int	ft_handle_keypress(int keysym, t_cub *data)
{
	t_event_handlers	event_handler;

	if (!data->active_canvas)
		return (0);
	ft_destroy_window_button(keysym, data);
	event_handler = ((t_canvas *)(data->active_canvas))->event_handlers;
	if (event_handler.on_keypress)
		return (event_handler.on_keypress(keysym,
				(void *)data->active_canvas,
				data));
	return (0);
}
