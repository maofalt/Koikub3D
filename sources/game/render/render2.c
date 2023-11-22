/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:44:11 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/22 18:54:00 by olimarti         ###   ########.fr       */
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
#define CEIL_COLOR 0xFF1D1D39
#define FLOOR_COLOR 0xFF1F6E91
#define WALL_COLOR 0xFF949DA8


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

static inline void	draw_vertical_line(
			t_canvas *canvas,
			const int x,
			int top,
			const int bottom,
			const t_color *const color
			)
{
	int					offset;

	assert(x >= 0);
	assert(x < canvas->size.x);
	assert(top >= 0);
	assert(bottom <= canvas->size.y);
	while (top < bottom)
	{

		offset = top * canvas->size.x + x;
		canvas->pixels[offset] = *color;
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

int project_wall(t_3d_render *render,
					t_segment_d *wall,
					t_segment_d *projected_top,
					t_segment_d *projected_bottom
					)
{
	wall->point_a.z = wall->data.floor;
	wall->point_b.z = wall->data.floor;
	if (project_segment(render, *wall, projected_bottom))
		return (1);
	wall->point_a.z = wall->data.ceil;
	wall->point_b.z = wall->data.ceil;
	if (project_segment(render, *wall, projected_top))
		return (1);
	if (projected_bottom->point_a.x == projected_bottom->point_b.x)
		return (1);
	return (0);
}


static inline void	draw_solid_wall_line(
	const t_3d_render *const render,
	int x,
	const double top,
	const double bottom
	)
{
	assert (x < render->canvas->size.x);
	const double	old_bottom = render->bottom_array[x];
	const double	old_top = render->top_array[x];
	t_color			color;

	render->top_array[x] = fmax(top, render->top_array[x]);
	render->bottom_array[x] = fmin(bottom, render->bottom_array[x]);
	color.d = WALL_COLOR;
	draw_vertical_line(render->canvas, x, render->top_array[x],
		render->bottom_array[x], &color);
	color.d = CEIL_COLOR;
	draw_vertical_line(render->canvas, x, old_top,
		render->top_array[x], &color);
	color.d = FLOOR_COLOR;
	draw_vertical_line(render->canvas, x, render->bottom_array[x],
		old_bottom, &color);
}

static inline void	draw_portal_wall_line(
	const t_3d_render *const render,
	int x,
	const double top,
	const double bottom
	)
{
	const double	old_bottom = render->bottom_array[x];
	const double	old_top = render->top_array[x];
	t_color			color;

	render->top_array[x] = fmax(top, render->top_array[x]);
	render->bottom_array[x] = fmin(bottom, render->bottom_array[x]);
	color.d = CEIL_COLOR;
	draw_vertical_line(render->canvas, x, old_top,
		render->top_array[x], &color);
	color.d = FLOOR_COLOR;
	draw_vertical_line(render->canvas, x, render->bottom_array[x],
		old_bottom, &color);
}

// static inline void	draw_portal_wall_line(
// 	const t_3d_render *const render,
// 	int x,
// 	const double top,
// 	const double bottom
// 	)
// {
// 	const double	old_bottom = render->bottom_array[x];
// 	const double	old_top = render->top_array[x];
// 	t_color			color;

// 	render->top_array[x] = fmax(top, render->top_array[x]);
// 	render->bottom_array[x] = fmin(bottom, render->bottom_array[x]);

// 	// if (old_top <= 0)
// 	// {
// 	color.d = CEIL_COLOR;
// 	// }
// 	// else
// 	// 	color.d = 0xFF0000FF;

// 	draw_vertical_line(render->canvas, x, old_top,
// 		render->top_array[x], &color);
// 	color.d = FLOOR_COLOR;
// 	draw_vertical_line(render->canvas, x, render->bottom_array[x],
// 		old_bottom, &color);
// }

void	draw_solid_wall(
	t_3d_render *render,
	t_segment_d	*wall,
	double left,
	double right
	)
{
	t_segment_d		projected_top;
	t_segment_d		projected_bot;
	double			coef_top;
	double			coef_bot;

	if (project_wall(render, wall, &projected_top, &projected_bot))
		return ;
	left = fmax(projected_top.point_a.x, left);
	right = fmin(projected_top.point_b.x, right);
	coef_bot = calc_seg_coef(&projected_bot);
	coef_top = calc_seg_coef(&projected_top);
	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);
	while (left < right)
	{
		draw_solid_wall_line(render, left, projected_top.point_a.y,
			projected_bot.point_a.y);
		projected_top.point_a.y += coef_top;
		projected_bot.point_a.y += coef_bot;
		++left;
	}
}


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


void	draw_filled_area_ceil(
	t_3d_render *render,
	t_segment_d	projected_bot,
	t_segment_d projected_top,
	double left,
	double right
	)
{
	double			coef_top;
	double			coef_bot;

	left = fmax(projected_top.point_a.x, left);
	right = fmin(projected_top.point_b.x, right);
	coef_bot = calc_seg_coef(&projected_bot);
	coef_top = calc_seg_coef(&projected_top);
	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);
	t_color color = {.d = WALL_COLOR};
	int x = left;
	while (x < right)
	{
		double bot = fmax(projected_bot.point_a.y, render->top_array[(int)x]);
		draw_vertical_line(render->canvas, x,
			render->top_array[(int)x], bot, &color);
		render->top_array[(int)x] = bot;
		// render->bottom_array[(int)x] = fmin(projected_bot.point_a.y, render->bottom_array[(int)x]);
		projected_top.point_a.y += coef_top;
		projected_bot.point_a.y += coef_bot;

		++x;
	}
}


void	draw_filled_area_floor(
	t_3d_render *render,
	t_segment_d	projected_bot,
	t_segment_d projected_top,
	double left,
	double right
	)
{
	double			coef_top;
	double			coef_bot;

	left = fmax(projected_top.point_a.x, left);
	right = fmin(projected_top.point_b.x, right);
	coef_bot = calc_seg_coef(&projected_bot);
	coef_top = calc_seg_coef(&projected_top);
	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);
	t_color color = {.d = WALL_COLOR};
	int x = left;
	while (x < right)
	{
		double top = fmin(projected_top.point_a.y, render->bottom_array[x]);
		draw_vertical_line(render->canvas, x, top,
			render->bottom_array[x], &color);
		render->bottom_array[x] = top;
		projected_top.point_a.y += coef_top;
		projected_bot.point_a.y += coef_bot;

		++x;
	}
}

void	draw_portal_ceil_adjustment(
	t_3d_render *render,
	t_segment_d	*portal_top,
	double left,
	double right
	)

{
	t_segment_d	*other_side_portal = NULL;
	t_segment_d	other_portal_top;

	other_side_portal = portal_top->data.data.portal.destination;
	other_side_portal->point_a.z = other_side_portal->data.ceil;
	other_side_portal->point_b.z = other_side_portal->data.ceil;
	if (project_segment(render, *other_side_portal, &other_portal_top))
		return ;

	if (portal_top->data.ceil < other_side_portal->data.ceil)
	{
		draw_filled_area_ceil(render, other_portal_top, *portal_top, left, right); //TODO use pointer instead
	}
}

void	draw_portal_floor_adjustment(
	t_3d_render *render,
	t_segment_d	*portal_bot,
	double left,
	double right
	)

{
	t_segment_d	*other_side_portal = NULL;
	t_segment_d	other_portal_bot;

	other_side_portal = portal_bot->data.data.portal.destination;
	other_side_portal->point_a.z = other_side_portal->data.floor;
	other_side_portal->point_b.z = other_side_portal->data.floor;
	if (project_segment(render, *other_side_portal, &other_portal_bot))
		return ;

	if (portal_bot->data.floor > other_side_portal->data.floor)
	{
		draw_filled_area_floor(render, *portal_bot, other_portal_bot, left, right);
	}
}


void	draw_portal_wall(
	t_3d_render *render,
	t_segment_d	*wall,
	double left,
	double right
	)
{
	t_segment_d		projected_top;
	t_segment_d		projected_bot;
	double			coef_top;
	double			coef_bot;

	if (project_wall(render, wall, &projected_top, &projected_bot))
		return ;
	left = fmax(projected_top.point_a.x, left);
	right = fmin(projected_top.point_b.x, right);
	coef_bot = calc_seg_coef(&projected_bot);
	coef_top = calc_seg_coef(&projected_top);
	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);
	t_render_item_queue		new_item_queue;
	if (left < right)
	{
		new_item_queue.left = left;
		new_item_queue.right = right;
		new_item_queue.portal = wall->data.data.portal.destination;
		circular_queue_add(render->queue, &new_item_queue);
	}
	double bot_y = projected_bot.point_a.y;
	double top_y = projected_top.point_a.y;
	int x = left;
	while (x < right)
	{
		draw_portal_wall_line(render, x, top_y,
			bot_y);
		top_y += coef_top;
		bot_y += coef_bot;
		++x;
	}
	projected_top.data = wall->data;
	projected_bot.data = wall->data;
	draw_portal_ceil_adjustment(render, &projected_top, left, right);
	draw_portal_floor_adjustment(render, &projected_bot, left, right);
}

// void	draw_portal_wall(
// 	t_3d_render *render,
// 	t_segment_d	*wall,
// 	double left,
// 	double right
// 	)
// {
// 	t_segment_d		projected_top;
// 	t_segment_d		projected_bot;
// 	double			coef_top;
// 	double			coef_bot;

// 	if (project_wall(render, wall, &projected_top, &projected_bot))
// 		return ;
// 	left = fmax(projected_top.point_a.x, left);
// 	right = fmin(projected_top.point_b.x, right);
// 	coef_bot = calc_seg_coef(&projected_bot);
// 	coef_top = calc_seg_coef(&projected_top);
// 	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
// 	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
// 	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
// 	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);
// 	t_render_item_queue		new_item_queue;
// 	if (left < right)
// 	{
// 		new_item_queue.left = left;
// 		new_item_queue.right = right;
// 		new_item_queue.portal = wall->data.data.portal.destination;
// 		circular_queue_add(render->queue, &new_item_queue);
// 	}
// 	while (left < right)
// 	{
// 		draw_portal_wall_line(render, left, projected_top.point_a.y,
// 			projected_bot.point_a.y);
// 		projected_top.point_a.y += coef_top;
// 		projected_bot.point_a.y += coef_bot;
// 		++left;
// 	}
// }


static void	render_portal(
	t_3d_render *render,
	t_render_item_queue *item_queue,
	t_segment_d *segment)
{
	// t_segment_d				projected_seg;
	// t_render_item_queue		new_item_queue;

	// if (project_segment(render, *segment, &projected_seg) == 0)
	// {
	// 	projected_seg.point_a.y -= 100;
	// 	projected_seg.point_b.y -= 100;


	// 	new_item_queue.left = fmax(projected_seg.point_a.x, item_queue->left);
	// 	new_item_queue.right = fmin(projected_seg.point_b.x, item_queue->right);
	// 	new_item_queue.portal = segment->data.data.portal.destination;
	// 	// printf("----%f, %f\n", new_item_queue.left, new_item_queue.right);
	// 	if (new_item_queue.left < new_item_queue.right)
	// 	{

	// 		projected_seg.point_b.x = new_item_queue.right;
	// 		projected_seg.point_a.x = new_item_queue.left;
	// 		draw_segment_canvas(render->canvas, &projected_seg,
	// 			(t_color){.d = 0xFF0000FF});
	// 		draw_portal_wall_line(render, segment, new_item_queue.left, new_item_queue.right);
	// 		// circular_queue_add(render->queue, &new_item_queue);
	// 	}
	// }
	draw_portal_wall(render, segment, item_queue->left, item_queue->right);
}

void	render_sector(
	t_3d_render *render,
	t_render_item_queue *item_queue,
	t_tree_node *node
	)
{
	t_list					*seg_lst;
	t_segment_d				*segment;

	seg_lst = ((t_bsp_tree_node_data *)node->data)->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		if (segment->data.type == PORTAL)
		{
			if (segment != item_queue->portal)
				render_portal(render, item_queue, segment);
		}
		else
		{
			draw_solid_wall(render, (t_segment_d *)seg_lst->content,
				item_queue->left, item_queue->right);
		}
		seg_lst = seg_lst->next;
	}
}

void	render_3d_draw(__attribute_maybe_unused__ t_3d_render *render)
{
	t_tree_node				*node;
	t_render_item_queue		item_queue;

	for (int i = 0; i < render->canvas->size.x; i++)
	{
		render->top_array[i] = 0;//render->canvas->size.y;
		render->bottom_array[i] = render->canvas->size.y;
	} //TODO, maybe use a flag system instead


	node = bsp_search_point(render->map->bsp,
			vector4d_to_point2d(&render->camera->pos));
	item_queue.left = 0;
	item_queue.portal = NULL;
	item_queue.right = render->canvas->size.x;
	while (node)
	{
		render_sector(render, &item_queue, node);
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

