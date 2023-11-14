/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:44:11 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/14 05:19:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "map_to_edges.h"
#include "bsp_builder.h"
#include "maths_utils.h"

#define CAMERA_PROXIMITY 0.01

typedef struct s_render_item_queue
{
	double		right;
	double		left;
	t_segment_d	*sector;
}	t_render_item_queue;

t_vector4d	transform_camera_relative_point(t_vector4d point, t_camera *camera)
{
	t_vector4d	relative_point;

	point.vec = point.vec - camera->pos.vec;
	relative_point.x = point.x * camera->dir.y - point.y * camera->dir.x;
	relative_point.y = point.x * camera->dir.x + point.y * camera->dir.y;
	relative_point.z = point.z;
	relative_point.w = point.w;
	return (relative_point);
}

t_segment_d	transform_camera_relative_segment(
	t_segment_d segment,
	t_camera *camera)
{
	segment.point_a = transform_camera_relative_point(segment.point_a, camera);
	segment.point_b = transform_camera_relative_point(segment.point_b, camera);
	return (segment);
}

t_vector4d	project_point(t_3d_render *render, t_vector4d point)
{
	t_vector4d	transformed_point;

	transformed_point.x = -point.x * 16 / point.y;
	transformed_point.y = point.z / point.y;
	transformed_point.z = point.y;
	transformed_point.w = 0;
	transformed_point.vec *= 16;
	transformed_point.vec += render->middle.vec;
	return (transformed_point);
}

int	relative_segment_clip_front(t_segment_d *segment)
{
	t_segment_d	horizontal;
	t_vector4d	intersect;

	horizontal = (t_segment_d){.point_a = {{1, CAMERA_PROXIMITY, 0, 0}},
		.point_b = {{10, CAMERA_PROXIMITY, 0, 0}}};
	if (segment->point_a.y <= 0 && segment->point_b.y <= 0)
		return (1);
	if (segment->point_a.y <= CAMERA_PROXIMITY
		|| segment->point_b.y <= CAMERA_PROXIMITY)
	{
		intersect = point2d_to_vector4d_cpy(
				find_intersection(horizontal, *segment));
		intersect.y = CAMERA_PROXIMITY;
		if (segment->point_a.y < CAMERA_PROXIMITY)
		{
			intersect.z = segment->point_a.z;
			segment->point_a = intersect;
		}
		if (segment->point_b.y < CAMERA_PROXIMITY)
		{
			intersect.z = segment->point_b.z;
			segment->point_b = intersect;
		}
	}
	return (0);
}


int	project_segment(
	t_3d_render *render,
	t_segment_d segment,
	t_segment_d *projected_seg)
{
	segment = transform_camera_relative_segment(segment, render->camera);
	if (relative_segment_clip_front(&segment))
		return (1);
	segment.point_a = project_point(render, segment.point_a);
	segment.point_b = project_point(render, segment.point_b);
	*projected_seg = segment;
	return (0);
}


void	render_3d_draw(__attribute_maybe_unused__ t_3d_render *render)
{
	t_list		*node;
	t_segment_d	transformed_seg;
	t_segment_d	*seg;

	node = render->map->segments;
	while (node)
	{
		printf("%p\n", node->content);
		seg = ((t_segment_d *)node->content);
		seg->point_a.z = seg->data.floor;
		seg->point_b.z = seg->data.floor;
		if (project_segment(render, *(t_segment_d *)node->content, &transformed_seg) == 0)
		{
			printf("---%p\n", node->content);
			draw_segment_canvas(render->canvas, &transformed_seg, (t_color){.d = 0xFFFFFFFF});
		}
		seg->point_a.z = seg->data.ceil;
		seg->point_b.z = seg->data.ceil;
		if (project_segment(render, *(t_segment_d *)node->content, &transformed_seg) == 0)
		{
			printf("---%p\n", node->content);
			draw_segment_canvas(render->canvas, &transformed_seg, (t_color) {.d = 0xFFF00FFF});
		}
		node = node->next;
	}
}

void	game_render(t_cub *data)
{
	t_canvas	*canvas;

	canvas = data->game_data.game_view_render.canvas;
	fill_canvas(
		canvas,
		(t_color){.d = 0xFF000000});
	render_3d_draw(&data->game_data.game_view_render);
	canvas_to_mlx_image(data->screen,
		canvas);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->screen.mlx_img, 0, 0);
}

//-----------

void	render_3d_destroy(t_3d_render *render)
{
	free(render->top_array);
	free(render->bottom_array);
	render->bottom_array = NULL;
	render->top_array = NULL;
}

int	render_3d_init(t_3d_render *render,
	t_canvas *canvas,
	t_camera *camera,
	t_map_data *map)
{
	render->canvas = canvas;
	render->camera = camera;
	render->map = map;
	render->middle.x = canvas->size.x / 2;
	render->middle.y = canvas->size.y / 2;
	render->middle.w = 0;
	render->middle.z = 0;
	render->top_array = ft_calloc(canvas->size.x, sizeof(int));
	render->bottom_array = malloc(canvas->size.x * sizeof(int));
	if (render->top_array == NULL || render->bottom_array == NULL)
	{
		render_3d_destroy(render);
		return (1);
	}
	return (0);
}

int	game_render_init(t_cub  *data)
{
	t_canvas	*canvas;

	canvas = get_canvas_from_list(data->canvas_list, MAP);
	return (render_3d_init(&data->game_data.game_view_render, canvas,
		&data->game_data.state.player_camera, &data->game_data.map_data));
}

void	game_render_destroy(t_cub *data)
{
	render_3d_destroy(&data->game_data.game_view_render);
}

