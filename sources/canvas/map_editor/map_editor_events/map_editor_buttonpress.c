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

int	map_canvas_handle_zoom(
	int zoom_direction,
	void *self,
	t_cub *data)
{
	t_matrix3x3		scale;
	t_canvas		*map_canvas;

	map_canvas = (t_canvas *)self;
	if (zoom_direction == 1)
	{
		scale = scaling_matrix((t_point2d){{1.05, 1.05}});
	}
	else
	{
		scale = scaling_matrix((t_point2d){{0.95, 0.95}});
	}
	// map_canvas->transformation_matrix
	// 	= matrix_multiply(map_canvas->transformation_matrix, scale);
	// if (push_matrix_op(&map_canvas->matrix_operations,
	// 		scale))
	//return (1);
	if (apply_matrix_transformation(map_canvas, scale))
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
		map_canvas_handle_zoom(1, self,  data);
	if (buttonsym == 5)
		map_canvas_handle_zoom(-1, self,  data);
	return (0);
}
