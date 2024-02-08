	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_posterization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:11:34 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 02:32:46 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "maths_utils.h"
#include "render_3D.h"
#include "structures.h"
#include <math.h>

t_color_64	shader_posterization(t_color_64 original_color, t_3d_render *render)
{
	const uint16_t levels = render->camera->effects.posterization.levels;

	if (render->camera->effects.posterization.enabled)
	{
		original_color.r = original_color.r / levels * levels;
		original_color.g = original_color.g / levels * levels;
		original_color.b = original_color.b / levels * levels;
	}
	return (original_color);
}
