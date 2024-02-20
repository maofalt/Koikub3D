/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:23:36 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 04:06:27 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_3D_H
# define RENDER_3D_H

# include "structures.h"

# define CAMERA_PROXIMITY 0.001
# define RENDER_QUEUE_SIZE 128
# define CEIL_COLOR 0x0
// #define CEIL_COLOR 0xFF1D1D39
// #define FLOOR_COLOR 0xFF1F6E91
# define FLOOR_COLOR 0x0
# define WALL_COLOR 0xFF949DA8

int				render_3d_init(t_3d_render *render, t_canvas *canvas,
					t_camera *camera, t_map_data *map);

int				render_init_lights(t_3d_render *render);
void			render_destroy_lights(t_3d_render *render);
int				light_spawn_default(t_3d_render *render);
void			light_destroy(t_3d_render *render, int id);

void			render_3d_destroy(t_3d_render *render);

void			render_3d_draw(t_3d_render *render);

void			render_3d_flush_to_canvas(t_3d_render *render);

void			render_wall(t_3d_render *render, t_segment_d *wall, double left,
					double right);

void			render_portal(t_3d_render *render, t_segment_d *portal,
					double left, double right);

typedef struct s_render_item_queue
{
	double		right;
	double		left;
	t_segment_d	*portal;
}				t_render_item_queue;

void			draw_portal_floor_offset(t_3d_render *render,
					t_segment_d *portal_bot, double left, double right);

void			draw_portal_ceil_offset(t_3d_render *render,
					t_segment_d *portal_top, double left, double right);

void			draw_portal_offset(t_3d_render *render, t_segment_d *portal_bot,
					double left, double right);

void			draw_textured_surface(t_3d_render *render, t_segment_d *wall,
					double left, double right);

void			update_portal_ceil_floor_buffer(const t_3d_render *const render,
					int x, const double top, const double bottom);

int				project_wall(t_3d_render *render, t_segment_d *wall,
					t_segment_d *projected_top, t_segment_d *projected_bottom);

t_segment_d		transform_camera_relative_segment(t_segment_d segment,
					t_camera *camera);

t_tree_node		*bsp_search_point(t_tree_node *tree, t_point2d point);
int				relative_segment_clip_front(t_segment_d *segment);

// SHADERS

void			compute_lights_visibility(t_3d_render *render);

t_color_64		shader_camera_lens_flare(t_color_64 original_color, int offset,
					t_3d_render *render);
t_color			shader_small_camera_displacement(t_color original_color,
					int offset, t_3d_render *render);

//DEFFERED SHADING
t_color_64		shader_deferred_shading(t_color_64 original_color, int offset,
					t_3d_render *render);
double			calc_light_cone(
					const t_light *const light,
					t_vector4d *light_dir
					);
double			calc_light_distance_attenuation(
					const t_vector4d *const light_pos,
					const t_vector4d *const world_pos);

double			calc_light_normal_diffuse(
					t_vector4d *normal,
					t_vector4d *light_dir);

double			calc_light_intensity(
					t_3d_render *render,
					const t_light *const light,
					t_vector4d world_pos,
					t_vector4d normal);

//--------
t_color_64		shader_normal_view(t_color_64 original_color, int offset,
					t_3d_render *render);

t_color_64		shader_posterization(t_color_64 original_color,
					t_3d_render *render);

t_point2i		displacement_tilt(t_point2i old_pos, t_3d_render *render);
t_point2i		displacement_wave(t_point2i old_pos, t_3d_render *render);

// UTILS

t_vector4d		transform_camera_relative_point(t_vector4d point,
					t_camera *camera);
t_vector4d		reverse_transform_camera_relative_point(t_vector4d relative_point,
					t_camera *camera);
t_vector4d		project_point(t_3d_render *render, t_vector4d point);
int				check_ray_reach_dest(t_vector4d origin, t_vector4d dest,
					t_3d_render *render);

// TEXTURE MAPPING UTILS

double			calc_wall_texture_repeat_factor_x(t_segment_d *segment);

double			calc_wall_texture_repeat_factor_y(t_segment_d *segment);

double			calc_wall_texture_offset(__attribute_maybe_unused__ t_segment_d *segment);

void			texture_mapping_calc_u(t_texture_mapping_data *data);

void			draw_billboard(t_3d_render *render, t_billboard *billboard);

#endif
