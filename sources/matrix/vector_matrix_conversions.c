/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_matrix_conversions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2023/12/03 21:33:23 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_vector4d	point2d_to_vector4d(t_point2d *point)
{
	t_vector4d	result;

	result.x = point->x;
	result.y = point->y;
	result.z = 1;
	result.w = 0;
	return (result);
}

t_vector4d	point2i_to_vector4d(t_point2i *point)
{
	t_vector4d	result;

	result.x = point->x;
	result.y = point->y;
	result.z = 1;
	result.w = 0;
	return (result);
}

t_point2d	vector4d_to_point2d(t_vector4d *vec4d)
{
	t_point2d	point2d;

	point2d.x = vec4d->x;
	point2d.y = vec4d->y;
	return (point2d);
}

t_matrix3x3	get_inverse_transformation_matrix(t_matrix3x3 matrix)
{
	t_matrix3x3	inverse;

	if (!invert_matrix(matrix, &inverse))
		return (inverse);
	else
		return (identity_matrix());
}

t_point2i	back_transform_point_by_matrix(t_vector4d point, t_matrix3x3 matrix)
{
	t_point2i			result;

	result.x = round(matrix.row[0].x * point.x
			+ matrix.row[0].y * point.y
			+ matrix.row[0].z * point.z);
	result.y = round(matrix.row[1].x * point.x
			+ matrix.row[1].y * point.y
			+ matrix.row[1].z * point.z);
	return (result);
}

t_vector4d	point2d_to_vector4d_cpy(t_point2d point)
{
	t_vector4d	result;

	result.x = point.x;
	result.y = point.y;
	result.z = 1;
	result.w = 0;
	return (result);
}

t_point2d	vector4d_to_point2d_cpy(t_vector4d vec4d)
{
	t_point2d	point2d;

	point2d.x = vec4d.x;
	point2d.y = vec4d.y;
	return (point2d);
}
