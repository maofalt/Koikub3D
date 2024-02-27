/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_portal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 05:14:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 23:50:54 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "draw_utils.h"
#include "structures_utils.h"
#include "render_3D.h"

void	update_full_portal_buffers(
	t_3d_render *render,
	t_segment_d *portal,
	double left,
	double right)
{
	t_segment_d	projected_top;
	t_segment_d	projected_bot;
	double		coef_top;
	double		coef_bot;
	int			x;

	if (project_wall(render, portal, &projected_top, &projected_bot))
		return ;
	coef_bot = calc_segment_coef(&projected_bot);
	coef_top = calc_segment_coef(&projected_top);
	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
	x = left;
	while (x < (int)(right))
	{
		update_portal_ceil_floor_buffer(render, x,
			projected_top.point_a.y, projected_bot.point_a.y);
		projected_top.point_a.y += coef_top;
		projected_bot.point_a.y += coef_bot;
		++x;
	}
}

void	render_portal(
	t_3d_render *render,
	t_segment_d *portal,
	double left,
	double right)
{
	t_segment_d			projected_top;
	t_segment_d			projected_bot;
	t_render_item_queue	new_item_queue;
	t_segment_d			*other_side_portal;

	if (project_wall(render, portal, &projected_top, &projected_bot))
		return ;
	left = fmax(projected_top.point_a.x, left);
	right = fmin(projected_top.point_b.x, right);
	draw_portal_offset(render, portal, left, right);
	other_side_portal = portal->data.data.portal.destination;
	if (((int)left) < (int)(right))
	{
		new_item_queue.left = left;
		new_item_queue.right = right;
		new_item_queue.portal = other_side_portal;
		circular_queue_add(render->queue, &new_item_queue);
	}
	update_full_portal_buffers(render, portal, left, right);
	update_full_portal_buffers(render, other_side_portal, left, right);
}
