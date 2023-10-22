/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_on_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/17 06:03:29 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

int	map_visualizer_draw(t_cub *data)
{
	if (data->win_ptr == NULL)
		return (1);
	if (data->update == NO_UPDATE)
		return (0);
	if (data->update & FULL_REDRAW)
	{
		redraw_scene(data,
			get_canvas_from_list(data->canvas_list, MAP));
	}
	canvas_to_mlx_image(data->screen,
		get_canvas_from_list(data->canvas_list, MAP));
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr,
		data->screen.mlx_img, 0, 0);
	data->update = NO_UPDATE;
	usleep(10);
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
