/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor_keypressing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2023/12/03 21:55:43 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"

int	map_editor_handle_rotation(int keysim, t_cub *data, void *map_canvas)
{
	t_map_editor_data	*map_editor;
	const double		angle = 3.14159265 / 128.0;
	int					ret;

	(void)data;
	map_editor = &((t_canvas *)map_canvas)->data.map_editor;
	ret = 1;
	if (keysim == XK_a)
		ret = -1;
	if (apply_rotation_at_position(
			map_editor,
			ret * angle,
			(t_point2d){{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}}))
		return (1);
	return (0);
}

int	process_key(int keysym, t_point2i pos, t_canvas *map_canvas)
{
	t_map_editor_data	*map_editor;

	map_editor = &((t_canvas *)map_canvas)->data.map_editor;
	if (keysym == LEFT_KEY || keysym == RIGHT_KEY
		|| keysym == UP_KEY || keysym == DOWN_KEY)
	{
		if (apply_matrix_transformation(map_editor,
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
	if (keysym == XK_a || keysym == XK_d)
		map_editor_handle_rotation(keysym, data, map_canvas);
	data->update = FULL_REDRAW;
	return (ret);
}
