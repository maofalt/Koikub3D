/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 05:15:17 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/04 05:34:07 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "structures.h"
#include "structures_utils.h"

void	render_wall(
		t_3d_render *render,
		t_segment_d *wall,
		double left,
		double right)
{
	draw_textured_surface(render, wall, left, right);
}
