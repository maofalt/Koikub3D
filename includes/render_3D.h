/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:23:36 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/24 22:33:32 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "structures.h"

#define CAMERA_PROXIMITY 0.0001
#define RENDER_QUEUE_SIZE 128
#define CEIL_COLOR 0xFF1D1D39
#define FLOOR_COLOR 0xFF1F6E91
#define WALL_COLOR 0xFF949DA8


int		render_3d_init(t_3d_render *render,
			t_canvas *canvas,
			t_camera *camera,
			t_map_data *map);

void	render_3d_destroy(t_3d_render *render);

void	draw_portal_floor_offset(
	t_3d_render *render,
	t_segment_d	*portal_bot,
	double left,
	double right
	);


void	draw_portal_ceil_offset(
	t_3d_render *render,
	t_segment_d	*portal_top,
	double left,
	double right
	);


void	draw_wall_texture(
		t_3d_render *render,
		t_segment_d	*wall,
		double left,
		double right
	);
