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

void	redraw_scene(t_cub *data, t_canvas *canvas)
{
	t_list		*current_segment;
	t_matrix3x3	invert_matrix;
	t_segment_d	segment;	
	t_color		color;

	(void)data;
	ft_memset(canvas->pixels, 0,
		canvas->size.x * canvas->size.y * sizeof(t_color));
	current_segment = canvas->segments;
	color = (t_color){{255, 255, 255, 255}};
	invert_matrix
		= get_inverse_transformation_matrix(canvas->transformation_matrix);
	while (current_segment)
	{
		segment = *(t_segment_d *)current_segment->content;
		draw_line_on_map(canvas,
			back_transform_point_by_matrix(segment.point_a, invert_matrix),
			back_transform_point_by_matrix(segment.point_b, invert_matrix),
			color);
		current_segment = current_segment->next;
	}
}

int	ft_destroy_window(t_cub *data)
{	
	free_everything(*data);
	exit(1);
	return (0);
}

int	ft_handle_keyrelease(int keysym, t_cub *data)
{
	(void)data;
	if (keysym == XK_Escape)
		ft_printf("Escape released\n");
	return (0);
}

static int ft_handle_zoom(int zoom_direction, t_cub *data)
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
	if (push_matrix_op(map_canvas->matrix_operations,
			scale))
		return (1);
	map_canvas->transformation_matrix
		= matrix_multiply(map_canvas->transformation_matrix, scale);
	redraw_scene(data, map_canvas);
	return (0);
}

static int	ft_handle_rotation(int keysim, t_cub *data)
{
	const double	angle = 3.14159265 / 8.0;
	t_matrix3x3		rotation;
	t_canvas		*map_canvas;	

	map_canvas = get_canvas_from_list(data->canvas_list, MAP);
	if (keysim == A_KEY)
		rotation = rotation_matrix(-angle);
	else
		rotation = rotation_matrix(angle);
	if (push_matrix_op(map_canvas->matrix_operations, rotation))
		return (1);
	map_canvas->transformation_matrix
		= matrix_multiply(map_canvas->transformation_matrix, rotation);
	return (0);
}

int	ft_handle_keypress(int keysym, t_cub *data)
{
	t_canvas		*map_canvas;
	t_matrix3x3		matrix_transformation;

	ft_destroy_window_button(keysym, data);
	map_canvas = get_canvas_from_list(data->canvas_list, MAP);
	// if (keysym == W_KEY || keysym == S_KEY || keysym == D_KEY
	// 	|| keysym == A_KEY || keysym == LEFT_KEY || keysym == RIGHT_KEY)
	// 	ft_movements_keys(keysym, data);
	if (keysym == LEFT_KEY)
	{
		matrix_transformation = translation_matrix((t_point2d){{-5, 0}});
		map_canvas->transformation_matrix = matrix_multiply(
				map_canvas->transformation_matrix, matrix_transformation);
		if (push_matrix_op(map_canvas->matrix_operations,
				matrix_transformation))
			return (1);
	}
	if (keysym == RIGHT_KEY)
	{
		matrix_transformation = translation_matrix((t_point2d){{5, 0}});
		map_canvas->transformation_matrix = matrix_multiply(
				map_canvas->transformation_matrix, matrix_transformation);
		if (push_matrix_op(map_canvas->matrix_operations,
				matrix_transformation))
			return (1);
	}
	if (keysym == UP_KEY)
	{
		matrix_transformation = translation_matrix((t_point2d){{0, 5}});
		map_canvas->transformation_matrix = matrix_multiply(
				map_canvas->transformation_matrix, matrix_transformation);
		if (push_matrix_op(map_canvas->matrix_operations,
				matrix_transformation))
			return (1);	
	}
	if (keysym == DOWN_KEY)
	{
		matrix_transformation = translation_matrix((t_point2d){{0, -5}});
		map_canvas->transformation_matrix = matrix_multiply(
				map_canvas->transformation_matrix, matrix_transformation);
		if (push_matrix_op(map_canvas->matrix_operations,
				matrix_transformation))
			return (1);
	}
	if (keysym == A_KEY || keysym == D_KEY)
		ft_handle_rotation(keysym, data);
	data->update = 1;
	return (0);
}

int	ft_handle_boutonpress(int buttonsym, int x, int y, t_cub *data)
{
	t_canvas		*map_canvas;
	const t_color	white_color = (t_color){{255, 255, 255, 255}};

	map_canvas = get_canvas_from_list(data->canvas_list, MAP);
	if (buttonsym == 1)
	{
		data->is_drawing = 1;
		start_drawing(map_canvas, (t_point2i){{x, y}});
		copy_canvas_to_temp(data->canvas_list);
	}
	if (buttonsym == 3)
	{
		data->is_drawing = 0;
		end_drawing(map_canvas, (t_point2i){{x, y}}, white_color);
	}
	if (buttonsym == 4)
	{
		printf("zoom in\n");
		ft_handle_zoom(1, data);
	}
	if (buttonsym == 5)
	{
		printf("zoom out\n");
		ft_handle_zoom(-1, data);
	}
	data->update = 1;
	return (0);
}

int	ft_handle_mousemotion(int x, int y, t_cub *data)
{
	t_canvas		*map_canvas;
	const t_color	white_color = (t_color){{255, 255, 255, 255}};

	map_canvas = get_canvas_from_list(data->canvas_list, MAP);
	if (data->is_drawing && !data->update)
	{
		copy_temp_to_canvas(data->canvas_list);
		update_drawing(map_canvas, (t_point2i){{x, y}}, white_color);
		data->update = 1;
	}
	return (0);
}
