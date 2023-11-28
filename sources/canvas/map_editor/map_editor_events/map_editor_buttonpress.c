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

//zooming at mouse position
int	map_canvas_handle_zoom(
	int zoom_direction,
	void *self,
	t_cub *data,
	t_point2i mouse_pos)
{
	t_canvas		*map_canvas;
	double			zoom;

	map_canvas = (t_canvas *)self;
	zoom = 1.05;
	if (zoom_direction == 1)
		zoom = 0.95;
	if (apply_zoom_at_position(map_canvas, zoom,
			(t_point2d){{mouse_pos.x, mouse_pos.y}}))
		return (1);
	data->update |= FULL_REDRAW;
	return (0);
}

int	map_canvas_handle_boutonpress(
	int buttonsym,
	t_point2i mouse_pos,
	void *self,
	t_cub *data)
{
	(void)mouse_pos;
	if (buttonsym == 1)
	{
		data->drawing = NOT_DRAWING;
		data->update |= LINE_REDRAW;
		data->update &= ~NO_UPDATE;
	}
	if (buttonsym == 3 && data->update & LINE_REDRAW)
	{
		data->drawing = END_DRAWING;
		data->update |= LINE_REDRAW;
	}
	if (buttonsym == 4)
		map_canvas_handle_zoom(1, self,  data, mouse_pos);
	if (buttonsym == 5)
		map_canvas_handle_zoom(-1, self,  data, mouse_pos);
	return (0);
}
