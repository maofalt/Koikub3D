/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:23:36 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/18 15:45:01 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

#define CAMERA_PROXIMITY 0.001
#define RENDER_QUEUE_SIZE 128
#define CEIL_COLOR 0x0
// #define CEIL_COLOR 0xFF1D1D39
// #define FLOOR_COLOR 0xFF1F6E91
#define FLOOR_COLOR 0x0
#define WALL_COLOR 0xFF949DA8

int		render_3d_init(t_3d_render *render,
					   t_canvas *canvas,
					   t_camera *camera,
					   t_map_data *map);

void	render_init_lights(t_3d_render *render);

void	render_3d_destroy(t_3d_render *render);

void	render_3d_draw(t_3d_render *render);

void	render_3d_flush_to_canvas(t_3d_render *render);


typedef struct s_render_item_queue
{
	double right;
	double left;
	t_segment_d *portal;
} t_render_item_queue;

void draw_portal_floor_offset(
	t_3d_render *render,
	t_segment_d *portal_bot,
	double left,
	double right);

void draw_portal_ceil_offset(
	t_3d_render *render,
	t_segment_d *portal_top,
	double left,
	double right);

void draw_portal_offset(
	t_3d_render *render,
	t_segment_d *portal_bot,
	double left,
	double right);

void draw_wall_texture(
	t_3d_render *render,
	t_segment_d *wall,
	double left,
	double right);

void update_portal_ceil_floor_buffer(
	const t_3d_render *const render,
	int x,
	const double top,
	const double bottom);

int project_wall(t_3d_render *render,
				 t_segment_d *wall,
				 t_segment_d *projected_top,
				 t_segment_d *projected_bottom);

t_segment_d transform_camera_relative_segment(
	t_segment_d segment,
	t_camera *camera);

t_tree_node *bsp_search_point(t_tree_node *tree, t_point2d point);
int relative_segment_clip_front(t_segment_d *segment);

// SHADERS

t_color shader_torch(t_color original_color, int offset, int width, int height, t_3d_render *render);

t_color shader_deferred_shading(t_color original_color, int offset, t_3d_render *render, double time_mouvement);
