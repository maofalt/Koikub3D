/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2023/10/14 16:41:39 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_point2d	transform_point_by_matrix(t_point2i point, t_matrix3x3 matrix)
{
	t_vector4d	homogenous_point;
	t_point2d	result;

	homogenous_point = point2i_to_vector4d(&point);
	result.x = matrix.row[0].x * homogenous_point.x
		+ matrix.row[0].y * homogenous_point.y
		+ matrix.row[0].z * homogenous_point.z;
	result.y = matrix.row[1].x * homogenous_point.x
		+ matrix.row[1].y * homogenous_point.y
		+ matrix.row[1].z * homogenous_point.z;
	return (result);
}

t_vector4d	transform_homogenous_point_by_matrix(t_vector4d point,
	t_matrix3x3 matrix)
{
	t_vector4d	result;

	result.x = matrix.row[0].x * point.x
		+ matrix.row[0].y * point.y
		+ matrix.row[0].z * point.z;
	result.y = matrix.row[1].x * point.x
		+ matrix.row[1].y * point.y
		+ matrix.row[1].z * point.z;
	return (result);
}

t_point2d	apply_transformations_to_point(t_point2i point,
	t_list *matrix_list)
{
	t_vector4d	hom_point;
	t_vector4d	transformed_point;
	t_point2d	result;
	t_list		*node;

	hom_point = point2i_to_vector4d(&point);
	node = matrix_list;
	while (node)
	{
		transformed_point = transform_homogenous_point_by_matrix(hom_point,
				*(t_matrix3x3 *)(node->content));
		hom_point = transformed_point;
		node = node->next;
	}
	ft_lstclear(&matrix_list, free);
	result = vector4d_to_point2d(&hom_point);
	return (result);
}
