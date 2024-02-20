/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_billboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 02:48:31 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 05:50:48 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "structures.h"
#include "maths_utils.h"
#include "ressources_managers.h"

static void	_orient_segment(t_segment_d *segment, t_vector4d *center)
{
	t_vector4d	tmp;

	if (point_segment_side(segment, center) == SIDE_LEFT)
	{
		tmp = segment->point_a;
		segment->point_a = segment->point_b;
		segment->point_b = tmp;
		segment->data.normal.vec = -segment->data.normal.vec;
	}
}

void	draw_transparent_surface(
				t_3d_render *render,
				t_segment_d *surface
				);

t_segment_d	_convert_billboard_to_seg(
	t_3d_render *render,
	t_billboard billboard)
{
	t_segment_d		surface_segment;

	surface_segment.point_a = billboard.pos;
	surface_segment.point_b = billboard.pos;
	surface_segment.point_a.x -= billboard.size.x / 2 * billboard.right.x;
	surface_segment.point_a.y -= billboard.size.x / 2 * billboard.right.y;
	surface_segment.point_a.z = 0;
	surface_segment.point_b.x += billboard.size.x / 2 * billboard.right.x;
	surface_segment.point_b.y += billboard.size.x / 2 * billboard.right.y;
	surface_segment.point_b.z = 0;
	surface_segment.data.normal = billboard.dir;
	_orient_segment(&surface_segment, &render->camera->pos);
	surface_segment.data.ceil = billboard.pos.z - billboard.size.y / 2;
	surface_segment.data.floor = billboard.pos.z + billboard.size.y / 2;
	surface_segment.data.data.wall.texture = billboard.texture;
	surface_segment.data.size = sqrt(billboard.size.x * billboard.size.x
			+ billboard.size.y * billboard.size.y);
	surface_segment.data.type = WALL;
	surface_segment.data.data.wall.size = surface_segment.data.size;
	surface_segment.data.data.wall.height = 10;
	return (surface_segment);
}

//TODO consider add raycast visibility check
// if (check_ray_reach_dest(render->camera->pos, billboard->pos, render))
void	draw_billboard(t_3d_render *render, t_billboard *billboard)
{
	t_vector4d		pos_screen;
	t_segment_d		surface_segment;

	pos_screen = transform_camera_relative_point(billboard->pos,
			render->camera);
	if (pos_screen.y > 0)
	{
		{
			surface_segment = _convert_billboard_to_seg(render, *billboard);
			draw_transparent_surface(render, &surface_segment);
		}
	}
}
