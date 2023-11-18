/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:44:11 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/18 19:27:14 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "map_to_edges.h"
#include "bsp_builder.h"
#include "maths_utils.h"
#include <assert.h>

#define CAMERA_PROXIMITY 0.0001
#define RENDER_QUEUE_SIZE 128

// typedef struct s_render_item_queue
// {
// 	double		right;
// 	double		left;
// 	t_segment_d	*sector;
// }	t_render_item_queue;

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
	if (segment.point_a.x < segment.point_b.x)
	{
		*projected_seg = segment;
	}
	else
	{
		projected_seg->point_a = segment.point_b;
		projected_seg->point_b = segment.point_a;
	}
	return (0);
}

// void	draw_wall(t_3d_render *render, t_segment_d	wall, double left, double right)
// {
// 	t_segment_d	transformed_seg;
// 	t_segment_d	*wall;


// 	wall.point_a.z = wall.data.floor;
// 	wall.point_b.z = wall.data.floor;
// 	if (project_segment(render, wall, &transformed_seg) == 0)
// 	{
// 		if (transformed_seg.point_a.)
// 		draw_segment_canvas(render->canvas, &transformed_seg, (t_color){.d = 0xFFFFFFFF});
// 	}
// 	wall.point_a.z = wall.data.ceil;
// 	wall.point_b.z = wall.data.ceil;
// 	if (project_segment(render, wall, &transformed_seg) == 0)
// 	{
// 		draw_segment_canvas(render->canvas, &transformed_seg, (t_color) {.d = 0xFFF00FFF});
// 	}
// }


// void	draw_filled_wall(t_3d_render *render, t_segment_d	wall, double left, double right)
// {
// 	t_segment_d	transformed_seg;
// 	t_segment_d	*wall;


// 	wall.point_a.z = wall.data.floor;
// 	wall.point_b.z = wall.data.floor;
// 	if (project_segment(render, wall, &transformed_seg) == 0)
// 	{
// 		if (transformed_seg.point_a.)
// 		draw_segment_canvas(render->canvas, &transformed_seg, (t_color){.d = 0xFFFFFFFF});
// 	}
// 	wall.point_a.z = wall.data.ceil;
// 	wall.point_b.z = wall.data.ceil;
// 	if (project_segment(render, wall, &transformed_seg) == 0)
// 	{
// 		draw_segment_canvas(render->canvas, &transformed_seg, (t_color) {.d = 0xFFF00FFF});
// 	}
// }
////-----------------------------


// static inline 	void	le_put_pixel_on_virtual_canvas(t_canvas *canvas,
// 	t_point2i *coord,
// 	const t_color *color)
// {
// 	int	offset;

// 	// if (coord->x >= 0 && coord->x < canvas->size.x && coord->y >= 0
// 	// 	&& coord->y < canvas->size.y)
// 	// {
// 		offset = coord->y * canvas->size.x + coord->x;
// 		canvas->pixels[offset] = *color;
// 	// }
// }

// static inline void	draw_vertical_line(t_canvas *canvas, int x, int top, int bottom)
// {
// 	t_point2i			cursor;
// 	const t_color		color = (t_color) {.d = 0xFFFFFFFF};

// 	cursor.x = x;
// 	cursor.y = top;
// 	// assert(cursor.x >= 0);
// 	// assert(cursor.y >= 0);
// 	// assert(cursor.x <= canvas->size.x);
// 	// assert(cursor.y <= canvas->size.y);
// 	while (cursor.y <= bottom)
// 	{
// 		le_put_pixel_on_virtual_canvas(canvas, &cursor, &color);
// 		++cursor.y;
// 	}
// }

// static inline 	void	le_put_pixel_on_virtual_canvas(t_canvas *canvas,
// 	t_point2i *coord,
// 	const t_color *color)
// {
// 	int	offset;

// 	// if (coord->x >= 0 && coord->x < canvas->size.x && coord->y >= 0
// 	// 	&& coord->y < canvas->size.y)
// 	// {
// 		offset = coord->y * canvas->size.x + coord->x;
// 		canvas->pixels[offset] = *color;
// 	// }
// }

static inline void	draw_vertical_line(
			t_canvas *canvas,
			int x,
			int top,
			int bottom
			)
{
	int					offset;

	// assert(cursor.x >= 0);
	// assert(cursor.y >= 0);
	// assert(cursor.x <= canvas->size.x);
	// assert(cursor.y <= canvas->size.y);
	while (top <= bottom)
	{
		offset = top * canvas->size.x + x;
		canvas->pixels[offset] = (t_color) {.d = 0xFFFFFFFF};
		++top;
	}
}

double	calc_seg_coef(
			t_segment_d *segment
			)
{
	t_point2d	delta;

	delta.x = segment->point_b.x - segment->point_a.x;
	delta.y = segment->point_b.y - segment->point_a.y;
	assert(delta.x != 0);
	return (delta.y / fabs(delta.x));
}

void	draw_filled_wall(t_3d_render *render, t_segment_d	wall, double left, double right)
{
	t_segment_d		projected_segment_top;
	t_segment_d		projected_segment_bot;
	double			coef_top;
	double			coef_bot;


	wall.point_a.z = wall.data.floor;
	wall.point_b.z = wall.data.floor;
	if (project_segment(render, wall, &projected_segment_bot))
		return ;
	wall.point_a.z = wall.data.ceil;
	wall.point_b.z = wall.data.ceil;
	if (project_segment(render, wall, &projected_segment_top))
		return ;
	if (projected_segment_bot.point_a.x == projected_segment_bot.point_b.x)
		return ;
	coef_bot = calc_seg_coef(&projected_segment_bot);
	coef_top = calc_seg_coef(&projected_segment_top);
	left = fmax(projected_segment_top.point_a.x, left);
	projected_segment_top.point_a.y = projected_segment_top.point_a.y + coef_top * (left - projected_segment_top.point_a.x);
	projected_segment_top.point_a.x = left;
	right = fmin(projected_segment_top.point_b.x, right);
	projected_segment_top.point_b.y = projected_segment_top.point_b.y + coef_top * (right - projected_segment_top.point_b.x);
	projected_segment_top.point_b.x = right;

	projected_segment_bot.point_a.y = projected_segment_bot.point_a.y + coef_bot * (left - projected_segment_bot.point_a.x);
	projected_segment_bot.point_a.x = left;
	projected_segment_bot.point_b.y = projected_segment_bot.point_b.y + coef_bot * (right - projected_segment_bot.point_b.x);
	projected_segment_bot.point_b.x = right;
	// draw_segment_canvas(render->canvas, &projected_segment_bot, (t_color) {.d = 0xFFF00FFF});
	// draw_segment_canvas(render->canvas, &projected_segment_top, (t_color) {.d = 0xFFFFFFFF});

		// printf("%f %f\n", projected_segment_top.point_a.y,  projected_segment_bot.point_a.y);
	while (left < right)
	{
//
		render->top_array[(int)left]    = fmax(projected_segment_top.point_a.y, render->top_array[(int)left]);
		render->bottom_array[(int)left] = fmin(projected_segment_bot.point_a.y, render->bottom_array[(int)left]);
		draw_vertical_line(render->canvas, left, render->top_array[(int)left], render->bottom_array[(int)left]);
		// printf("%f, %f, %f\n", left, render->top_array[(int)left], render->bottom_array[(int)left]);
		++left;
		projected_segment_top.point_a.y += coef_top;
		projected_segment_bot.point_a.y += coef_bot;
	}

}

// void	draw_wall(t_cub *data, t_canvas *canvas, t_segment_d wall)
// {
// 	double			coef_top;
// 	double			coef_bot;
// 	t_segment_d		projected_segment_top;
// 	t_segment_d		projected_segment_bot;

// 	// wall.data.ceil = ;
// 	wall.point_a.z = wall.data.ceil;
// 	wall.point_b.z = wall.data.ceil;
// 	if (project_segment(data, wall, &projected_segment_top))
// 	{
// 		//Hidden
// 	}
// 	coef_top = calc_seg_coef(&projected_segment);

// 	wall.point_a.z = wall.data.floor;
// 	wall.point_b.z = wall.data.floor;
// 	if (project_segment(data, canvas, wall, &projected_segment))
// 	{
// 		//Hidden
// 	}
// 	coef_bot = calc_seg_coef(&projected_segment);

// 	x_left = fmax(projected_segment.point_a.x, area.top_left.x);
// 	x_right = fmin(projected_segment.point_b.x, area.top_right.x);

// 	while (x_left <= x_right)
// 	{
// 		y_ceil = project_segment.
// 		draw_vertical_line(canvas, x_left, )
// 		++x_left;
// 	}



// }


////-----------------------------



// void	render_3d_draw(__attribute_maybe_unused__ t_3d_render *render)
// {
// 	t_list		*node;
// 	t_segment_d	transformed_seg;
// 	t_segment_d	*seg;

// 	node = render->map->segments;
// 	while (node)
// 	{
// 		printf("%p\n", node->content);
// 		seg = ((t_segment_d *)node->content);
// 		seg->point_a.z = seg->data.floor;
// 		seg->point_b.z = seg->data.floor;
// 		if (project_segment(render, *(t_segment_d *)node->content, &transformed_seg) == 0)
// 		{
// 			printf("---%p\n", node->content);
// 			draw_segment_canvas(render->canvas, &transformed_seg, (t_color){.d = 0xFFFFFFFF});
// 		}
// 		seg->point_a.z = seg->data.ceil;
// 		seg->point_b.z = seg->data.ceil;
// 		if (project_segment(render, *(t_segment_d *)node->content, &transformed_seg) == 0)
// 		{
// 			printf("---%p\n", node->content);
// 			draw_segment_canvas(render->canvas, &transformed_seg, (t_color) {.d = 0xFFF00FFF});
// 		}
// 		node = node->next;
// 	}
// }

t_tree_node	*bsp_search_point(t_tree_node	*tree, t_point2d point)
{
	t_tree_node	*child;
	t_segment_d	separator;
	double		point_side;

	if (!tree)
		return (NULL);
	if (!tree->left || !tree->right)
		return (tree);
	separator = ((t_bsp_tree_node_data *)tree->data)->separator;
	point_side = point_space_partitioning(&separator, &point);
	if (point_side > 0)
		child = bsp_search_point(tree->right, point);
	else
		child = bsp_search_point(tree->left, point);
	if (child != NULL)
		return (child);
	return (NULL);
}

typedef struct s_render_item_queue
{
	double					right;
	double					left;
	t_segment_d				*portal;
}	t_render_item_queue;


void	render_sector(t_3d_render *render, t_render_item_queue item_queue, t_tree_node *node)
{
	t_list					*seg_lst;
	t_segment_d				*segment;
	t_segment_d				projected_seg;
	t_render_item_queue		new_item_queue;

	seg_lst = ((t_bsp_tree_node_data*)node->data)->sector_segments;

	while (seg_lst)
	{
		segment = seg_lst->content;
		if (segment->data.type == PORTAL)
		{
		//-------------------

			if (segment != item_queue.portal && project_segment(render, *segment, &projected_seg) == 0)
			{
				projected_seg.point_a.y -= 100;
				projected_seg.point_b.y -= 100;


				new_item_queue.left =  fmax(projected_seg.point_a.x, item_queue.left);
				new_item_queue.right = fmin(projected_seg.point_b.x, item_queue.right);
				new_item_queue.portal = segment->data.data.portal.destination;
				// printf("----%f, %f\n", new_item_queue.left, new_item_queue.right);
				if (new_item_queue.left < new_item_queue.right)
				{

				projected_seg.point_b.x = new_item_queue.right;
				projected_seg.point_a.x = new_item_queue.left;
				draw_segment_canvas(render->canvas, &projected_seg, (t_color) {.d = 0xFF0000FF});
				//-------------------
					circular_queue_add(render->queue, &new_item_queue); //FIXME
				}
			}
		}
		else
		{
			draw_filled_wall(render, *(t_segment_d *)seg_lst->content, item_queue.left, item_queue.right);
		}
		seg_lst = seg_lst->next;
	}
}


void	render_3d_draw(__attribute_maybe_unused__ t_3d_render *render)
{
	t_tree_node				*node;
	// t_bsp_tree_node_data	*node_data;
	t_render_item_queue		item_queue;

	for (int i = 0; i < render->canvas->size.x; i++)
	{
		render->top_array[i] = 0;//render->canvas->size.y;
		render->bottom_array[i] = render->canvas->size.y;
	} //TODO, maybe use a flag system instead


	node = bsp_search_point(render->map->bsp,
		vector4d_to_point2d(&render->camera->pos));
	item_queue.left = 0;
	item_queue.right = render->canvas->size.x;
	while (node)
	{
		render_sector(render, item_queue, node);
		if (circular_queue_pop(render->queue, &item_queue) == 0)
			node = item_queue.portal->data.data.portal.tree_node_ptr;
		else
			node = NULL;
	}
}

void	game_render(t_cub *data)
{
	t_canvas	*canvas;

	canvas = data->game_data.game_view_render.canvas;

	fill_canvas(
		canvas,
		(t_color){.d = 0x00000000});
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
	circular_queue_destroy(render->queue);
	render->bottom_array = NULL;
	render->top_array = NULL;
	render->queue = NULL;
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
	render->top_array = ft_calloc(canvas->size.x, sizeof(double));
	render->bottom_array = ft_calloc(canvas->size.x, sizeof(double));
	render->queue = circular_queue_create(RENDER_QUEUE_SIZE,
		sizeof(t_render_item_queue));
	if (render->top_array == NULL
		|| render->bottom_array == NULL
		|| render->queue == NULL)
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

