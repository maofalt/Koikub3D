/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2023/10/16 21:35:09 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "draw_utils.h"

int	ft_handle_boutonpress(int buttonsym, int x, int y, t_cub *data)
{
	t_event_handlers	event_handler;

	if (!data->active_canvas)
		data->active_canvas = data->canvas_list;
	data->mouse_pos = (t_point2i){{x, y}};
	if (buttonsym == 1)
	{	
		data->active_canvas
			= (t_canvas *)detect_clicked_canvas(data, data->mouse_pos);
	}
	event_handler = ((t_canvas *)(data->active_canvas))->info.event_handlers;
	if (event_handler.on_boutonpress)
		return (event_handler.on_boutonpress(buttonsym,
				(t_point2i){{x, y}},
			(void *)data->active_canvas,
			data));
	return (0);
}
