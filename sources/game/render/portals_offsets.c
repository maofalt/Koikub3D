/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals_offsets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:33:45 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/23 13:31:36 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "draw_utils.h"
#include "structures.h"
#include "map_to_edges.h"
#include "bsp_builder.h"
#include "maths_utils.h"
#include "render_3D.h"
#include <assert.h>

int	project_segment(
	t_3d_render *render,
	t_segment_d segment,
	t_segment_d *projected_seg);

double	calc_seg_coef(t_segment_d *segment);


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


void	draw_filled_area_ceil(
	t_3d_render *render,
	t_segment_d	*projected_bot,
	double left,
	double right
	)
{
	const t_color	color = (t_color){.d = WALL_COLOR};
	double			coef_bot;
	int				x;
	double			y;
	double			bot;

	left = fmax(projected_bot->point_a.x, left);
	x = left;
	right = fmin(projected_bot->point_b.x, right);
	coef_bot = calc_seg_coef(projected_bot);
	y = projected_bot->point_a.y + coef_bot * (left - projected_bot->point_a.x);
	while (x < right)
	{
		bot = fmax(y, render->top_array[x]);
		draw_vertical_line(render->canvas, x,
			render->top_array[(int)x], bot, &color);
		render->top_array[(int)x] = bot;
		y += coef_bot;
		++x;
	}
}

//TODO rename [prtal fill offset
void	draw_filled_area_floor(
	t_3d_render *render,
	t_segment_d *projected_top,
	double left,
	double right
	)
{
	const t_color	color = (t_color){.d = WALL_COLOR};
	int				x;
	double			y;
	double			coef_top;
	double			top;

	left = fmax(projected_top->point_a.x, left);
	right = fmin(projected_top->point_b.x, right);
	coef_top = calc_seg_coef(projected_top);
	x = left;
	y = projected_top->point_a.y + coef_top * (left - projected_top->point_a.x);
	while (x < right)
	{
		top = fmin(y, render->bottom_array[x]);
		draw_vertical_line(render->canvas, x, top,
			render->bottom_array[x], &color);
		render->bottom_array[x] = top;
		y += coef_top;
		++x;
	}
}

void	draw_portal_ceil_offset(
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
		draw_filled_area_ceil(render, &other_portal_top, left, right); //TODO use pointer instead
	}
}

void	draw_portal_floor_offset(
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
		draw_filled_area_floor(render, &other_portal_bot, left, right);
	}
}
