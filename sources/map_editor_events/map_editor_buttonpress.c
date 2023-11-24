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

int	ft_handle_zoom(int zoom_direction, t_cub *data)
{
	t_canvas		*map_canvas;
	t_matrix3x3		scale;

	map_canvas = get_canvas_from_list(data->canvas_list, MAP);
	if (zoom_direction == 1)
	{
		scale = scaling_matrix((t_point2d){{1.05, 1.05}});
	}
	else
	{
		scale = scaling_matrix((t_point2d){{0.95, 0.95}});
	}
	data->update |= FULL_REDRAW;
	map_canvas->transformation_matrix
		= matrix_multiply(map_canvas->transformation_matrix, scale);
	if (push_matrix_op(&map_canvas->matrix_operations,
			scale))
		return (1);
	return (0);
}

int	ft_handle_boutonpress(int buttonsym, int x, int y, t_cub *data)
{
	data->mouse_pos = (t_point2i){{x, y}};
	if (buttonsym == 1)
	{
		data->active_canvas = 
			(t_canvas *)detect_clicked_canvas(data, data->mouse_pos);
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
		ft_handle_zoom(1, data);
	if (buttonsym == 5)
		ft_handle_zoom(-1, data);
	return (0);
}
