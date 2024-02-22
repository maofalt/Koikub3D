/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light_cone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:57:01 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 04:09:44 by olimarti         ###   ########.fr       */
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

double	calc_light_cone(
		const t_light *const light,
		t_vector4d *light_dir
)
{
	double	cone;

	if (light->type != DIRECTIONAL_LIGHT)
		return (1);
	cone = _dot_product_3d(light_dir, &light->dir);
	if (cone < 0)
		return (0);
	cone = pow(cone, 5);
	cone *= 1 + cos(cone * 10) * 0.5;
	cone = fmax(0, cone);
	return (cone);
}
