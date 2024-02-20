/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_to_mlx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 19:27:57 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

/*
	Method that will cycle through all canvases of the data->canvas_list
	and apply pointer to function of each canvas.
	Only for canvas with the type UI, MAP, GAME
*/
int	apply_to_canvas(t_cub *data, t_canvas_func canvas_func)
{
	t_list		*current_canvas;
	t_canvas	*canvas;

	current_canvas = data->canvas_list;
	while (current_canvas)
	{
		canvas = (t_canvas *)current_canvas->content;
		if (is_valid_canvas(canvas))
		{
			if (canvas_func != NULL)
				canvas_func(canvas, data);
		}
		current_canvas = current_canvas->next;
	}
	return (0);
}

int	render(t_cub *data)
{
	t_canvas	*final_canvas;

	if (data->win_ptr == NULL)
		return (1);
	final_canvas = get_canvas_from_list(data->canvas_list, FINAL);
	if (!final_canvas)
		return (1);
	apply_to_canvas(data, render_base);
	merge_canvases(&data->canvas_list);
	canvas_to_mlx_image(data->screen, final_canvas);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->screen.mlx_img, 0, 0);
	return (0);
}

void	redraw_scene(t_cub *data, t_canvas *canvas)
{
	t_list		*current_segment;
	t_matrix3x3	invert_matrix;
	t_segment_d	segment;
	t_color		color;

	(void)data;
	ft_memset(canvas->pixels, 0,
		canvas->size.x * canvas->size.y * sizeof(t_color));
	current_segment = canvas->data.map_editor.segments;
	color = (t_color){{255, 255, 255, 255}};
	invert_matrix
		= get_inverse_transformation_matrix(
			canvas->data.map_editor.transformation_matrix);
	while (current_segment)
	{
		segment = *(t_segment_d *)current_segment->content;
		draw_line_on_map(canvas,
			back_transform_point_by_matrix(segment.point_a, invert_matrix),
			back_transform_point_by_matrix(segment.point_b, invert_matrix),
			color);
		current_segment = current_segment->next;
	}
	data->update &= ~FULL_REDRAW;
}
