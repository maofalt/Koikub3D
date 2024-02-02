/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_normal_view.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:11:34 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/02 18:58:16 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "maths_utils.h"
#include "render_3D.h"
#include "structures.h"
#include <math.h>

t_color_64	shader_normal_view(t_color_64 original_color, int offset,
		t_3d_render *render)
{
	if (render->buffers.depth[offset] != 0)
	{
		original_color.r = (render->buffers.normal[offset].x * 128) + 128;
		original_color.g = (render->buffers.normal[offset].y * 128) + 128;
		original_color.b = (render->buffers.normal[offset].z * 128) + 128;
	}
	// else
	// {
	// 	original_color.d = 0;
	// }
	return (original_color);
}
