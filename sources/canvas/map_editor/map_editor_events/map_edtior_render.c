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
#include "map_to_edges.h"

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

static void printfallsegments(t_list *current_segment)
{
	//print all segments data where they start where they end, and size 
	t_segment_d *segment;
	int i = 0;
	while (current_segment)
	{
	    segment = (t_segment_d *)current_segment->content; // Cast the content to t_segment_d
	    if (segment != NULL) // Check if segment is not NULL
	    {
			//printf("SEGMENTS  %d\n", i);
			//printf("\tstart: [%f, %f]", segment->point_a.x, segment->point_a.y);
	        //printf(" \tend: [%f, %f]", segment->point_b.x, segment->point_b.y);
			//calcuallte length and print it
			//printf("\tsize: %f\n", sqrt(pow(segment->point_b.x - segment->point_a.x, 2) + pow(segment->point_b.y - segment->point_a.y, 2)));
	        // printf("size: %d\n", ...); // Size is not a property of t_segment_d based on your example
	    }
	    current_segment = current_segment->next; // Move to the next element in the list
		i++;
	}
}

int	map_editor_render(void *self, t_cub *data)
{
	t_canvas	*map_editor = (t_canvas *)self;
	t_matrix3x3	scale;
	(void)scale;
	//printf("map_editor_render\n");
	if (map_editor->segments == NULL)
	{
		extract_edge_recursively(data->map, &map_editor->segments);
		printfallsegments(map_editor->segments);
		apply_matrix_transformation(map_editor,
			translation_matrix((t_point2d)
			{{-WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2}}));
		//scale = scaling_matrix((t_point2d){{0.5, 0.5}});
		// map_editor->transformation_matrix
		// 	= matrix_multiply(map_editor->transformation_matrix, scale);
		// if (push_matrix_op(&map_editor->matrix_operations, scale))
		// 	return (1);
		data->update |= FULL_REDRAW;
	}
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
