/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:35:00 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/29 19:42:27 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

static void	normalize_vector_3d(t_vector4d *vec)
{
	t_vector4d	product;
	double		reverse_lenght;

	product.vec = vec->vec;
	product.vec *= product.vec;
	reverse_lenght = 1 / sqrt(product.x + product.y + product.z);
	vec->vec *= reverse_lenght;
}

static t_vector4d	calc_segment_normal(t_segment_d *segment)
{
	t_vector4d	normal;

	normal.vec = segment->point_b.vec - segment->point_a.vec;
	normal = (t_vector4d){{-normal.y, normal.x, 0, 0}};
	normalize_vector_3d(&normal);
	return (normal);
}

void	compute_segment_normal(
	__attribute_maybe_unused__ t_game_data *game_data,
	t_segment_d *segment)
{
	segment->data.normal = calc_segment_normal(segment);
}
