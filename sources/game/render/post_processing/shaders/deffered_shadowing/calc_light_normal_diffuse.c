/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light_normal_diffuse.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:05:11 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 04:08:01 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "maths_utils.h"
#include "render_3D.h"

static inline double	_dot_product_3d(
	const t_vector4d *const vec1,
	const t_vector4d *const vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y + +vec1->z * vec2->z);
}

double	calc_light_normal_diffuse(t_vector4d *normal, t_vector4d *light_dir)
{
	const double	diffuse = fmax(_dot_product_3d(normal, light_dir), 0.0);

	return (diffuse);
}
