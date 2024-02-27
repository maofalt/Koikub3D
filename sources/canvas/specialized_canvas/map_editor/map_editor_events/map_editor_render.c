/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2024/02/27 00:47:58 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "draw_utils.h"
#include "map_to_edges.h"
#include "parsing.h"

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
		data->segments_list = canvas->data.map_editor.segments;
	}
	else if (data->drawing == DRAWING)
	{
		copy_temp_to_canvas(data->canvas_list);
		update_drawing(canvas, mouse_pos, (t_color){{255, 255, 255, 255}});
	}
}

//print all segments data where they start where they end, and size
// static void printfallsegments(t_list *current_segment)
// {
// 	t_segment_d *segment;
// 	int i = 0;
// 	while (current_segment)
// 	{
// 		segment = (t_segment_d *)current_segment->content;
// 		// Cast the content to t_segment_d
// 		if (segment != NULL) // Check if segment is not NULL
// 		{
// 			printf("SEGMENTS  %d\n", i);
// 			printf("\tstart: [%f, %f]",
// 			segment->point_a.x, segment->point_a.y);
// 			printf(" \tend: [%f, %f]",
// 				segment->point_b.x, segment->point_b.y);
// 			// calcuallte length and print it
// 			printf("\tsize: %f\n",
// 				sqrt(pow(segment->point_b.x - segment->point_a.x, 2)
// 					+ pow(segment->point_b.y - segment->point_a.y, 2)));
// 		}
// 		current_segment = current_segment->next;
//	// Move to the next element in the list
// 		i++;
// 	}
// }

//Autotcenter map in the screen
static int	auto_center_map(t_map_editor_data *map_editor, t_cub *data)
{
	t_point2d		map_center;
	t_point2d		scaled_map_center;
	t_point2d		scales;
	double			scale;

	data->mapwidth = get_map_width(data->map);
	data->mapheight = get_map_height(data->map);
	map_center = (t_point2d){{(data->mapwidth) / 2, data->mapheight / 2}};
	scales = (t_point2d){{(double)WINDOW_WIDTH / data->mapwidth,
		(double)WINDOW_HEIGHT / data->mapheight}};
	scale = scales.y;
	if (scales.x < scales.y)
		scale = scales.x;
	scaled_map_center = (t_point2d)
	{{map_center.x - ((WINDOW_WIDTH / 2) / scale),
		map_center.y - ((WINDOW_HEIGHT / 2) / scale)}};
	if (apply_zoom_at_position(map_editor, (1 / scale) * 1.0,
			scaled_map_center))
		return (1);
	return (0);
}

int	map_editor_render(void *self, t_cub *data)
{
	t_canvas			*map_editor;
	t_map_editor_data	*map_editor_data;

	map_editor = (t_canvas *)self;
	map_editor_data = &map_editor->data.map_editor;
	if (map_editor_data->segments == NULL)
	{
		extract_edge_recursively(data->map, &map_editor_data->segments);
		data->segments_list = map_editor_data->segments;
		auto_center_map(map_editor_data, data);
		data->update |= FULL_REDRAW;
	}
	if (data->update & LINE_REDRAW)
		handle_line_redraw(data);
	if (data->update & FULL_REDRAW)
	{
		redraw_scene(data, (t_canvas *)self);
		data->update = NO_UPDATE;
	}
	return (0);
}
