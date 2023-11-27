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

int	map_editor_handle_rotation(int keysim, t_cub *data, void *map_canvas)
{
	const double	angle = 3.14159265 / 128.0;
	t_matrix3x3		rotation;	

	(void)data;
	if (keysim == A_KEY)
		rotation = rotation_matrix(-angle);
	else
		rotation = rotation_matrix(angle);
	if (apply_matrix_transformation((t_canvas *)map_canvas, rotation))
		return (1);
	return (0);
}

int	process_key(int keysym, t_point2i pos, t_canvas *map_canvas)
{
	if (keysym == LEFT_KEY || keysym == RIGHT_KEY
		|| keysym == UP_KEY || keysym == DOWN_KEY)
	{
		if (apply_matrix_transformation(map_canvas,
				translation_matrix((t_point2d){{pos.x, pos.y}})))
			return (1);
	}
	return (0);
}

int	map_canvas_handle_keypress(int keysym, void *self, t_cub *data)
{
	int			ret;
	int			offset;
	t_canvas	*map_canvas;

	map_canvas = (t_canvas *)self;
	offset = 200;
	ret = 0;
	if (keysym == LEFT_KEY)
		ret += process_key(keysym, (t_point2i){{offset, 0}}, map_canvas);
	if (keysym == RIGHT_KEY)
		ret += process_key(keysym, (t_point2i){{-offset, 0}}, map_canvas);
	if (keysym == UP_KEY)
		ret += process_key(keysym, (t_point2i){{0, offset}}, map_canvas);
	if (keysym == DOWN_KEY)
		ret += process_key(keysym, (t_point2i){{0, -offset}}, map_canvas);
	if (keysym == A_KEY || keysym == D_KEY)
		map_editor_handle_rotation(keysym, data, map_canvas);
	data->update = FULL_REDRAW;
	return (ret);
}
