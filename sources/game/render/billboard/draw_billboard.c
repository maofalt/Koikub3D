/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_billboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 02:48:31 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/09 06:56:37 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "structures.h"
#include "maths_utils.h"


// void	draw_billboard(t_3d_render *render, t_billboard *billboard)
// {
// 	double		depth;
// 	t_vector4d	top_left_rel;
// 	t_vector4d	bot_right_;
// 	t_vector4d	top_left;
// 	t_vector4d	bot_right;
// 	t_point2i	cursor;
// 	t_point2i	cursor_max;


// 	billboard->size = (t_vector4d){{2, 2, 0, 0}};

// 	top_left = transform_camera_relative_point(billboard->pos, render->camera);
// 	// top_left.vec = //- billboard->size.vec;
// 	bot_right.x = top_left.x - billboard->size.x;
// 	bot_right.y = top_left.y;
// 	bot_right.z = top_left.z + billboard->size.y;

// 	printf("draw_billboard: --- top_left: %f %f %f\n", top_left.x, top_left.y, top_left.z);
// 	printf("draw_billboard: --- bot_right: %f %f %f\n", bot_right.x, bot_right.y, bot_right.z);

// 	if (top_left.y <= 0 || bot_right.y <= 0)
// 		return ;

// 	top_left = project_point(render, top_left);
// 	bot_right = project_point(render, bot_right);

// 	printf("*draw_billboard: top_left: %f %f %f\n", top_left.x, top_left.y, top_left.z);
// 	printf("*draw_billboard: bot_right: %f %f %f\n", bot_right.x, bot_right.y, bot_right.z);

// 	cursor.x = fmax((int)top_left.x, 0);
// 	cursor.y = fmax((int)top_left.y, 0);

// 	cursor_max.x = fmin((int)bot_right.x, render->width);
// 	cursor_max.y = fmin((int)bot_right.y, render->height);

// 	printf("draw_billboard: top_left: %f %f %f\n", top_left.x, top_left.y, top_left.z);
// 	printf("draw_billboard: bot_right: %f %f %f\n", bot_right.x, bot_right.y, bot_right.z);
// 	printf("draw_billboard: cursor_max: %d %d\n", cursor_max.x, cursor_max.y);
// 	printf("draw_billboard: cursor: %d %d\n", cursor.x, cursor.y);
// 	t_vector4d world_pos = (t_vector4d){{0, 0, 0, 0}};
// 	while (cursor.y < cursor_max.y)
// 	{
// 		cursor.x = fmax((int)top_left.x, 0);
// 		while (cursor.x < cursor_max.x)
// 		{
// 			depth = lerp(top_left.z, bot_right.z, (cursor.x - top_left.x) /
// 				(bot_right.x - top_left.x));
// 			// depth = 1;
// 			// if (depth < render->buffers.depth[cursor.x + cursor.y * render->width] || depth == 0)
// 			{
// 				double alpha = (cursor.x - top_left.x) / (bot_right.x - top_left.x);
// 				double beta = (cursor.y - top_left.y) / (bot_right.y - top_left.y);
// 				world_pos.x = lerp(alpha, top_left.x, bot_right.x);
// 				world_pos.z = lerp(beta, top_left.y, bot_right.y);


// 				render->buffers.color[cursor.x + cursor.y * render->width].d = 0xFFFFFFFF;
// 				render->buffers.depth[cursor.x + cursor.y * render->width] = depth;
// 				render->buffers.normal[cursor.x + cursor.y * render->width] = (t_vector4d){{0, 0, 1, 0}};


// 			}
// 			++cursor.x;
// 		}
// 		++cursor.y;
// 	}
// }

#include "ressources_managers.h"

static void	orient_segment(t_segment_d *segment, t_vector4d *center)
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

void	draw_billboard_3d(
		t_3d_render *render,
		t_segment_d *surface
		);

void	draw_billboard(t_3d_render *render, t_billboard billboard)
{
	t_segment_d		surface_segment;


	int	i;

	i = 0;
	while (i < render->width)
	{
		render->top_array[i] = 0;
		render->bottom_array[i] = render->height;
		++i;
	}

	// billboard.texture.texture = render->map->texture_manager->textures;
	// billboard.texture.offset = 0;
	// billboard.dir = (t_vector4d){{0, 1, 0, 0}};
	// billboard.right = (t_vector4d){{1, 0, 0, 0}};
	// billboard.size = (t_vector4d){{1, 1, 0, 0}};

	surface_segment.point_a = billboard.pos;
	surface_segment.point_b = billboard.pos;
	surface_segment.point_a.x -= billboard.size.x / 2 * billboard.right.x;
	surface_segment.point_a.y -= billboard.size.x / 2 * billboard.right.y;
	surface_segment.point_a.z = 0;
	surface_segment.point_b.x += billboard.size.x / 2 * billboard.right.x;
	surface_segment.point_b.y += billboard.size.x / 2 * billboard.right.y;
	surface_segment.point_b.z = 0;

	surface_segment.data.normal = billboard.dir;
	orient_segment(&surface_segment, &render->camera->pos);
	surface_segment.data.ceil = billboard.pos.z - billboard.size.y / 2;
	surface_segment.data.floor = billboard.pos.z + billboard.size.y / 2;
	surface_segment.data.data.wall.texture = billboard.texture;
	surface_segment.data.size = sqrt(billboard.size.x * billboard.size.x
			+ billboard.size.y * billboard.size.y);
	surface_segment.data.type = WALL;
	surface_segment.data.data.wall.size = surface_segment.data.size;
	surface_segment.data.data.wall.height = 10;
	printf("%d\n", texture_get_frame(surface_segment.data.data.wall.texture.texture)->size.x);

	// draw_textured_surface(render, &surface_segment, 0, render->width);
	draw_billboard_3d(render, &surface_segment);
}

void	draw_billboard_placeholder(t_3d_render *render, t_billboard *billboard)
{
	t_vector4d	pos_screen;

	pos_screen = transform_camera_relative_point(billboard->pos,
			render->camera);
	if (pos_screen.y > 0)
	{
		printf("draw_billboard_placeholder: pos: %f %f %f\n", billboard->pos.x,
			billboard->pos.y, billboard->pos.z);
		if (check_ray_reach_dest(render->camera->pos, billboard->pos, render))
		{
			draw_billboard(render, *billboard);
		}
	}
}
