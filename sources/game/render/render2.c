/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:44:11 by olimarti          #+#    #+#             */
/*   Updated: 2023/12/30 21:13:48 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "map_to_edges.h"
#include "bsp_builder.h"
#include "maths_utils.h"
#include "render_3D.h"
#include "ressources_managers.h"
#include <assert.h>

t_vector4d transform_camera_relative_point(t_vector4d point, t_camera *camera)
{
	t_vector4d relative_point;

	point.vec = point.vec - camera->pos.vec;
	relative_point.x = point.x * camera->dir.y - point.y * camera->dir.x;
	relative_point.y = point.x * camera->dir.x + point.y * camera->dir.y;
	relative_point.z = point.z;
	relative_point.w = point.w;
	return (relative_point);
}

t_segment_d transform_camera_relative_segment(
	t_segment_d segment,
	t_camera *camera)
{
	segment.point_a = transform_camera_relative_point(segment.point_a, camera);
	segment.point_b = transform_camera_relative_point(segment.point_b, camera);
	return (segment);
}

t_vector4d project_point(t_3d_render *render, t_vector4d point)
{
	t_vector4d transformed_point;

	transformed_point.x = -point.x * 16 / point.y;
	transformed_point.y = point.z / point.y;
	transformed_point.z = point.y;
	transformed_point.w = 0;
	transformed_point.vec *= 16;
	transformed_point.vec += render->middle.vec;
	return (transformed_point);
}

int relative_segment_clip_front(t_segment_d *segment)
{
	t_segment_d horizontal;
	t_vector4d intersect;

	horizontal = (t_segment_d){.point_a = {{1, CAMERA_PROXIMITY, 0, 0}},
							   .point_b = {{10, CAMERA_PROXIMITY, 0, 0}}};
	if (segment->point_a.y <= 0 && segment->point_b.y <= 0)
		return (1);
	if (segment->point_a.y <= CAMERA_PROXIMITY || segment->point_b.y <= CAMERA_PROXIMITY)
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

int project_segment(
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

static inline void draw_vertical_line(
	t_canvas *canvas,
	const int x,
	int top,
	const int bottom,
	const t_color *const color)
{
	int offset;

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

double calc_seg_coef(
	t_segment_d *segment)
{
	t_point2d delta;

	delta.x = segment->point_b.x - segment->point_a.x;
	delta.y = segment->point_b.y - segment->point_a.y;
	assert(delta.x != 0);
	return (delta.y / fabs(delta.x));
}

int project_wall(t_3d_render *render,
				 t_segment_d *wall,
				 t_segment_d *projected_top,
				 t_segment_d *projected_bottom)
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

static inline void draw_solid_wall_line(
	const t_3d_render *const render,
	int x,
	const double top,
	const double bottom)
{
	assert(x < render->canvas->size.x);
	const double old_bottom = render->bottom_array[x];
	const double old_top = render->top_array[x];
	t_color color;

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

static inline void draw_portal_wall_line(
	const t_3d_render *const render,
	int x,
	const double top,
	const double bottom)
{
	// const double	old_bottom = render->bottom_array[x];
	// const double	old_top = render->top_array[x];
	// t_color			color;

	render->top_array[x] = fmax(top, render->top_array[x]);
	render->bottom_array[x] = fmin(bottom, render->bottom_array[x]);
	// color.d = CEIL_COLOR;
	// draw_vertical_line(render->canvas, x, old_top,
	// render->top_array[x], &color);
	// color.d = FLOOR_COLOR;
	// draw_vertical_line(render->canvas, x, render->bottom_array[x],
	// 	old_bottom, &color);
}

void draw_solid_wall(
	t_3d_render *render,
	t_segment_d *wall,
	double left,
	double right)
{
	t_segment_d projected_top;
	t_segment_d projected_bot;
	double coef_top;
	double coef_bot;

	if (project_wall(render, wall, &projected_top, &projected_bot))
		return;
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

t_tree_node *bsp_search_point(t_tree_node *tree, t_point2d point)
{
	t_tree_node *child;
	t_segment_d separator;
	double point_side;

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
	double right;
	double left;
	t_segment_d *portal;
} t_render_item_queue;

void draw_portal_offset(
	t_3d_render *render,
	t_segment_d *portal_bot,
	double left,
	double right);

void render_portal(
	t_3d_render *render,
	t_segment_d *wall,
	double left,
	double right)
{
	t_segment_d projected_top;
	t_segment_d projected_bot;
	double coef_top;
	double coef_bot;

	if (project_wall(render, wall, &projected_top, &projected_bot))
		return;
	left = fmax(projected_top.point_a.x, left);
	right = fmin(projected_top.point_b.x, right);
	t_render_item_queue new_item_queue;
	if (left < right)
	{
		new_item_queue.left = left;
		new_item_queue.right = right;
		new_item_queue.portal = wall->data.data.portal.destination;
		circular_queue_add(render->queue, &new_item_queue);
	}
	coef_bot = calc_seg_coef(&projected_bot);
	coef_top = calc_seg_coef(&projected_top);
	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);
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
	// draw_portal_ceil_offset(render, &projected_top, left, right);
	// draw_portal_floor_offset(render, &projected_bot, left, right);
	draw_portal_offset(render, wall, left, right);
}

void render_sector(
	t_3d_render *render,
	t_render_item_queue *item_queue,
	t_tree_node *node)
{
	t_list *seg_lst;
	t_segment_d *segment;

	seg_lst = ((t_bsp_tree_node_data *)node->data)->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		if (segment->data.type == PORTAL)
		{
			if (segment != item_queue->portal)
				render_portal(render, segment,
							  item_queue->left, item_queue->right);
		}
		else
		{
			draw_wall_texture(render, (t_segment_d *)seg_lst->content,
							  item_queue->left, item_queue->right);
			// draw_solid_wall(render, (t_segment_d *)seg_lst->content,
			// 	item_queue->left, item_queue->right);
		}
		seg_lst = seg_lst->next;
	}
}

void render_3d_draw(t_3d_render *render)
{
	t_tree_node *node;
	t_render_item_queue item_queue;

	memset(render->g_buffer, 0,
		   render->canvas->size.x * render->canvas->size.y * sizeof(render->g_buffer[0]));
	for (int i = 0; i < render->canvas->size.x; i++)
	{
		render->top_array[i] = 0; // render->canvas->size.y;
		render->bottom_array[i] = render->canvas->size.y;
	} // TODO, maybe use a flag system instead

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

// double center_dist = (pow((screen_top + y) - (canvas->size.y/2) , 2) + pow(screen_x - (canvas->size.x/2), 2));

// 		double opacity = 0.1/ fmax(depth * depth, 1);

// 		// depth = depth / (center_dist/1000);
// 		// if (center_dist < 10000)
// 		// {
// 			// depth -= 1 / sqrt(center_dist);
// 			// depth =  1;
// 		opacity +=  (0.5 / (depth*1.5)) * fmin(((50000 * fmin(1000, depth) / (center_dist*2))), 4);
// 		// }

// 		opacity = fmin(opacity, 1);
// 		opacity = fmax(opacity, 0);
// 		canvas->pixels[offset].b *= opacity;
// 		canvas->pixels[offset].g *= opacity;
// 		canvas->pixels[offset].r *= opacity;
// 		canvas->pixels[offset].a *= opacity;

// __attribute__((optimize("-ffast-math")))
t_color shader_torch(t_color original_color, int offset, int width, int height, t_3d_render *render)
{
	int y = offset / width;
	int x = offset % width;
	double depth = render->g_buffer[offset].z;

	double center_dist = ((y - height / 2) * (y - height / 2)) + ((x - width / 2) * (x - width / 2));

	double opacity = 0.1 / fmax(depth * depth, 1);

	// depth = depth / (center_dist/1000);
	// if (center_dist < 10000)
	// {
	// depth -= 1 / sqrt(center_dist);
	// depth =  1;
	opacity += (0.5 / (depth * 1.5)) * fmin(((50000 * fmin(1000, depth) / (center_dist * 2))), 4);
	// }

	opacity = fmin(opacity, 1);
	opacity = fmax(opacity, 0);
	original_color.b *= opacity;
	original_color.g *= opacity;
	original_color.r *= opacity;
	original_color.a *= opacity;

	return (original_color);
}

double q_rsqrt(double number)
{
	// long i;
	// float x2, y;
	// const float threehalfs = 1.5F;

	// x2 = number * 0.5F;
	// y  = number;
	// i  = * ( long * ) &y;                       // evil floating point bit level hacking
	// i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	// y  = * ( double * ) &i;
	// y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	// // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return 1 / sqrt(number);
}
void normalize_vector_2d(t_vector4d *vec)
{
	double reverse_lenght = q_rsqrt(vec->x * vec->x + vec->y * vec->y);
	vec->vec[0] *= reverse_lenght;
	vec->vec[1] *= reverse_lenght;
}

void normalize_vector_3d(t_vector4d *vec)
{
	double reverse_lenght = q_rsqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->vec[0] *= reverse_lenght;
	vec->vec[1] *= reverse_lenght;
	vec->vec[2] *= reverse_lenght;
}

double dot_product_2d(t_vector4d *vec1, t_vector4d *vec2)
{
	// double result = vec1->x * vec2->x + vec1->y * vec2->y;
	double result = vec1->x * vec2->x + vec1->y * vec2->y;
	return result;
}
double dot_product_3d(t_vector4d *vec1, t_vector4d *vec2)
{
	// double result = vec1->x * vec2->x + vec1->y * vec2->y;
	double result = vec1->x * vec2->x + vec1->y * vec2->y + +vec1->z * vec2->z;
	return result;
}

// double point_cross_product()
// {
// 	t_vector4d	ab;
// 	t_vector4d	ap;
// 	double		cross_product;

// 	ab.vec = separator->point_b.vec - separator->point_a.vec;
// 	ap.vec = segment_point->vec - separator->point_a.vec;
// 	cross_product = ab.x * ap.y - ab.y * ap.x;
// }

typedef struct s_light
{
	t_vector4d pos;
	t_color color;
} t_light;

t_light lights[3] = {
	{ .pos = { .vec = { 2, 2, -1, 0 } }, .color = { .r = 1, .g = 0, .b = 0.5 } },
	{ .pos = { .vec = { 7, 9, 2, 0 } }, .color = { .r = 1, .g = 0, .b = 2 } },
	{ .pos = { .vec = { 20, 20, 0, 0 } }, .color = { .r = 5, .g = 1, .b = 0 } },

};

t_color shader_deferred_shading(t_color original_color, int offset, t_3d_render *render)
{

	// int y = offset / width;
	// int x = offset % width;
	t_g_buffer g_buff = render->g_buffer[offset];

	t_color lighting = original_color;
	double luminosity = 0.2;
	lighting.r *= luminosity;
	lighting.g *= luminosity;
	lighting.b *= luminosity;

	for (int i = 0; i < sizeof(lights) / sizeof(lights[0]); i++)
	{
		t_vector4d light_pos = lights[i].pos;
		light_pos = transform_camera_relative_point(light_pos, render->camera);

		t_vector4d light_dir = {.vec = {0, 0, 0, 0}};
		light_dir.vec = light_pos.vec - g_buff.world_pos.vec;
		normalize_vector_3d(&light_dir);

		double diffuse = fmax(dot_product_3d(&g_buff.normal, &light_dir), 0.0);
		double dist = sqrt((light_pos.x - g_buff.world_pos.x) * (light_pos.x - g_buff.world_pos.x) + (light_pos.y - g_buff.world_pos.y) * (light_pos.y - g_buff.world_pos.y) + (light_pos.z - g_buff.world_pos.z) * (light_pos.z - g_buff.world_pos.z));
		double attenuation = 1.0 / (dist);

		lighting.r += original_color.r * fmin(1, diffuse * attenuation * lights[i].color.r);
		lighting.g += original_color.g * fmin(1, diffuse * attenuation * lights[i].color.g);
		lighting.b += original_color.b * fmin(1, diffuse * attenuation * lights[i].color.b);
	}

	return lighting;
}

t_color shader_floor(t_color original_color, int offset, t_3d_render *render)
{
	// Calculate the floor color based on the offset
	int x = offset % render->canvas->size.x;
	int y = offset / render->canvas->size.x;
	t_color floor_color = {.r = 0, .g = 0, .b = 0};

	// Geometric tiling pattern
	int tile_size = 4;
	int tile_x = x / tile_size;
	int tile_y = y / tile_size;

	// Calculate the position of the current tile in world coordinates
	double world_tile_x = tile_x - render->camera->pos.x / tile_size;
	double world_tile_y = tile_y - render->camera->pos.y / tile_size;

	// Rotate the world coordinates based on camera direction
	double cos_theta = render->camera->dir.x;
	double sin_theta = render->camera->dir.y;

	// Add a counter to make the rotation continuously slow move
	static double rotation_counter;
	rotation_counter += 0.00000001; // Adjust the speed of rotation here

	double rotated_tile_x = world_tile_x * cos_theta - world_tile_y * sin_theta + rotation_counter;
	double rotated_tile_y = world_tile_x * sin_theta + world_tile_y * cos_theta + rotation_counter;

	// Apply a color pattern based on the rotated tile coordinates
	if ((int)rotated_tile_x % 2 == 0)
	{
		if ((int)rotated_tile_y % 2 == 0)
		{
			floor_color.r = 15;
			floor_color.g = 15;
			floor_color.b = 15;
		}
		else
		{
			floor_color.r = 0;
			floor_color.g = 0;
			floor_color.b = 0;
		}
	}
	else
	{
		if ((int)rotated_tile_y % 2 == 0)
		{
			floor_color.r = 0;
			floor_color.g = 0;
			floor_color.b = 0;
		}
		else
		{
			floor_color.r = 15;
			floor_color.g = 15;
			floor_color.b = 15;
		}
	}

	return floor_color;
}

t_color shader_motif(t_color original_color, int offset, t_3d_render *render)
{
	// Calculate the floor color based on the offset
	int x = offset % render->canvas->size.x;
	int y = offset / render->canvas->size.x;
	t_color floor_color = {.r = 0, .g = 0, .b = 0};

	// Geometric tiling pattern
	int tile_size = 5;
	int tile_x = x / tile_size;
	int tile_y = y / tile_size;

	// Calculate the position of the current tile in world coordinates
	double world_tile_x = tile_x - render->camera->pos.x / tile_size;
	double world_tile_y = tile_y - render->camera->pos.y / tile_size;

	// Rotate the world coordinates based on camera direction
	double cos_theta = render->camera->dir.x;
	double sin_theta = render->camera->dir.y;

	// Add a counter to make the rotation continuously slow move
	static double rotation_counter;
	rotation_counter += 0.0000001; // Adjust the speed of rotation here

	double rotated_tile_x = world_tile_x * cos_theta - world_tile_y * sin_theta + rotation_counter;
	double rotated_tile_y = world_tile_x * sin_theta + world_tile_y * cos_theta + rotation_counter;

	// Apply a color pattern based on the rotated tile coordinates
	if ((int)rotated_tile_x % 2 == 0)
	{
		if ((int)rotated_tile_y % 2 == 0)
		{
			floor_color.r = 3;
			floor_color.g = 3;
			floor_color.b = 3;
		}
		else
		{
			floor_color.r = 0;
			floor_color.g = 0;
			floor_color.b = 0;
		}
	}
	else
	{
		if ((int)rotated_tile_y % 2 == 0)
		{
			floor_color.r = 0;
			floor_color.g = 0;
			floor_color.b = 0;
		}
		else
		{
			floor_color.r = 3;
			floor_color.g = 3;
			floor_color.b = 3;
		}
	}

	original_color.r = fabs(original_color.r - floor_color.r);
	original_color.g = fabs(original_color.g - floor_color.g);
	original_color.b = fabs(original_color.b - floor_color.b);

	return (original_color);
}

unsigned int xorshift32(unsigned int *state)
{
	unsigned int x = *state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	*state = x;
	return x;
}
t_color shader_ceil(t_color original_color, int offset, t_3d_render *render)
{
	// Calculate the ceiling color based on the offset
	int x = offset % render->canvas->size.x;
	int y = offset / render->canvas->size.x;
	t_color ceiling_color = {.r = 0, .g = 0, .b = 0};

	if (y < render->canvas->size.y / 2)
	{
		ceiling_color.r = 5;
		ceiling_color.g = 5;
		ceiling_color.b = 5;
	}
	else
	{
		ceiling_color.r = 5;
		ceiling_color.g = 5;
		ceiling_color.b = 5;
	}

	// Apply the ceiling color to the original color
	original_color.r = (ceiling_color.r);
	original_color.g = (ceiling_color.g);
	original_color.b = (ceiling_color.b);

	// Add noisy effect
	static unsigned int state = 1;			 // Initial state for Xorshift
	unsigned int noise = xorshift32(&state); // Generate random noise value using Xorshift
	double noise_intensity = 3;				 // Adjust the intensity of the noise effect

	// Apply noise effect directly to the color components
	original_color.r += (double)noise / UINT_MAX * noise_intensity;
	original_color.g += (double)noise / UINT_MAX * noise_intensity;
	original_color.b += (double)noise / UINT_MAX * noise_intensity;

	return original_color;
}

// t_color
// shader_noise(t_color original_color, int offset, t_3d_render *render)
// {
// 	static unsigned int state = 1;			 // Initial state for Xorshift
// 	unsigned int noise = xorshift32(&state); // Generate random noise value using Xorshift
// 	double noise_intensity = 10;			 // Adjust the intensity of the noise effect

// 	// Apply noise effect directly to the color components
// 	original_color.r += (double)noise / UINT_MAX * noise_intensity;
// 	original_color.g += (double)noise / UINT_MAX * noise_intensity;
// 	original_color.b += (double)noise / UINT_MAX * noise_intensity;

// 	return original_color;
// }

static float _temp_sin(float val)
{
	return (sinf(val / 4.0) + 1.0) / 2.0 / 4.0 + 0.25;
}

t_color shader_noise(t_color original_color, int offset, t_3d_render *render)
{
	// int x = offset % render->canvas->size.x;
	// int y = offset / render->canvas->size.x;
	// static unsigned int tick = 0;

	// double diff_x = x - render->canvas->size.x / 2;
	// double diff_y = y - render->canvas->size.y / 2;
	// double diff_z = render->g_buffer[offset].world_pos.y;

	// // double dist = sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z);

	// double intensity = (sinf(tick / 10.0) + 1.0) / 2.0;

	// int val = (original_color.r + original_color.g + original_color.b) / 3;

	// Apply noise effect directly to the color components
	original_color.r = original_color.r / 16 * 16;
	original_color.g = original_color.g / 16 * 16;
	original_color.b = original_color.b / 16 * 16;

	// ++tick;

	return (original_color);
}

// #include <omp.h>
#include <stdio.h>

void post_process_frame(t_3d_render *render)
{
	const int max_offset = render->canvas->size.x * render->canvas->size.y;
	int i;

	// #pragma omp parallel for

	for (i = 0; i < max_offset; i++)
	{
		if (render->g_buffer[i].z > 0)
		{
			render->canvas->pixels[i] = shader_deferred_shading(render->canvas->pixels[i], i, render);
			// render->canvas->pixels[i] = shader_noise(render->canvas->pixels[i], i, render);
			// render->canvas->pixels[i] = shader_torch(render->canvas->pixels[i], i, render->canvas->size.x, render->canvas->size.y, render);
			render->canvas->pixels[i] = shader_motif(render->canvas->pixels[i], i, render);
		}
		else
		{
			render->canvas->pixels[i] = shader_floor(render->canvas->pixels[i], i, render);
		}
	}
}

void game_render(t_cub *data)
{
	t_canvas *canvas;

	texture_manager_update(&data->texture_manager);
	canvas = data->game_data.game_view_render.canvas;
	fill_canvas(
		canvas,
		(t_color){.d = 0x00000000});
	render_3d_draw(&data->game_data.game_view_render);
	post_process_frame(&data->game_data.game_view_render);
	canvas_to_mlx_image(data->screen,
						canvas);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
							data->screen.mlx_img, 0, 0);
}

//-----------

void render_3d_destroy(t_3d_render *render)
{
	free(render->top_array);
	free(render->bottom_array);
	free(render->g_buffer);
	circular_queue_destroy(render->queue);
	render->bottom_array = NULL;
	render->top_array = NULL;
	render->queue = NULL;
}

int render_3d_init(t_3d_render *render,
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
	render->g_buffer = ft_calloc(canvas->size.x * canvas->size.y,
								 sizeof(render->g_buffer[0]));
	render->queue = circular_queue_create(RENDER_QUEUE_SIZE,
										  sizeof(t_render_item_queue));
	if (render->top_array == NULL || render->bottom_array == NULL || render->g_buffer == NULL || render->queue == NULL)
	{
		render_3d_destroy(render);
		return (1);
	}
	return (0);
}

int game_render_init(t_cub *data, t_canvas *canvas)
{
	if (canvas == NULL)
		return (1);
	return (render_3d_init(&data->game_data.game_view_render, canvas,
						   &data->game_data.state.player_camera, &data->game_data.map_data));
}

void game_render_destroy(t_cub *data)
{
	render_3d_destroy(&data->game_data.game_view_render);
}
