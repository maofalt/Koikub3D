/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals_offsets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:33:45 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/12 21:57:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "draw_utils.h"
#include "structures.h"
#include "map_to_edges.h"
#include "bsp_builder.h"
#include "maths_utils.h"
#include "render_3D.h"
#include <assert.h>

void update_portal_ceil_floor_buffer(
	const t_3d_render *const render,
	int x,
	const double top,
	const double bottom
	)
{
	render->top_array[x] = fmax(top, render->top_array[x]);
	render->bottom_array[x] = fmin(bottom, render->bottom_array[x]);
}


void	draw_portal_offset(
	t_3d_render *render,
	t_segment_d	*portal_bot,
	double left,
	double right
	)

{
	t_segment_d	*other_side_portal = NULL;
	// t_segment_d	other_portal_bot;

	other_side_portal = portal_bot->data.data.portal.destination;
	other_side_portal->point_a.z = other_side_portal->data.floor;
	other_side_portal->point_b.z = other_side_portal->data.floor;
	// if (project_segment(render, *other_side_portal, &other_portal_bot))
	// 	return ;

	if (portal_bot->data.floor > other_side_portal->data.floor)
	{
		t_segment_d	padding_top;

		padding_top = *portal_bot;
		padding_top.data.floor = portal_bot->data.floor;
		padding_top.data.ceil = other_side_portal->data.floor;
		padding_top.data.data.wall.texture = portal_bot->data.data.portal.padding_texture_bottom;
		draw_wall_texture(render, &padding_top, left, right);
	}
	if (portal_bot->data.ceil < other_side_portal->data.ceil)
	{
		t_segment_d	padding_top;

		padding_top = *portal_bot;
		padding_top.data.ceil = portal_bot->data.ceil;
		padding_top.data.floor = other_side_portal->data.ceil;
		padding_top.data.data.wall.texture = portal_bot->data.data.portal.padding_texture_bottom;
		draw_wall_texture(render, &padding_top, left, right);
	}
}
