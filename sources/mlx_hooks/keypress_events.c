/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2024/02/04 22:23:19 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"

void	ft_destroy_window_button(int keysym, t_cub *data)
{
	if (keysym == XK_Escape)
	{
		mlx_loop_end(data->mlx_ptr);
	}
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

int	ft_handle_keyrelease(int keysym, t_cub *data)
{
	t_event_handlers	event_handler;

	if (!data->active_canvas)
		return (0);
	event_handler = ((t_canvas *)(data->active_canvas))->event_handlers;
	if (event_handler.on_keyrelease)
		return (event_handler.on_keyrelease(keysym,
				(void *)data->active_canvas,
				data));
	return (0);
}

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
