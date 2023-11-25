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

static void	handle_line_redraw(t_cub *data)
{
	const t_point2i	mouse_pos = data->mouse_pos;
	t_canvas		*canvas;

	canvas = get_canvas_from_list(data->canvas_list, MAP);
	if (data->drawing == NOT_DRAWING)
	{
		start_drawing(canvas, (t_point2i)mouse_pos);
		copy_canvas_to_temp(data->canvas_list);
		data->drawing = DRAWING;
	}
	else if (data->drawing & END_DRAWING)
	{
		end_drawing(canvas, mouse_pos, (t_color){{255, 255, 255, 255}});
		redraw_scene(data, canvas);
		data->drawing = NOT_DRAWING;
		data->update &= ~LINE_REDRAW;
		copy_canvas_to_temp(data->canvas_list);
	}
	else if (data->drawing == DRAWING)
	{
		copy_temp_to_canvas(data->canvas_list);
		update_drawing(canvas, mouse_pos, (t_color){{255, 255, 255, 255}});
	}
}

int	map_editor_render(void *self, t_cub *data)
{
	if (data->update & LINE_REDRAW)
		handle_line_redraw(data);
	if (data->update & FULL_REDRAW)
	{
		redraw_scene(data, get_canvas_from_list(data->canvas_list, FIN_TEMP));
		redraw_scene(data, (t_canvas *)self);
		data->update = NO_UPDATE;
	}
	return (0);
}