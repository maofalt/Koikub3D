/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_matrix_conversions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2024/02/20 19:20:35 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

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
