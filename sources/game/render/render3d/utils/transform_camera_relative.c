/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_camera_relative.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:10:48 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/30 20:56:23 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <assert.h>

t_vector4d	transform_camera_relative_point(t_vector4d point, t_camera *camera)
{
	t_vector4d	relative_point;

	point.vec = point.vec - camera->pos.vec;
	relative_point.x = point.x * camera->dir.y - point.y * camera->dir.x;
	relative_point.y = point.x * camera->dir.x + point.y * camera->dir.y;
	relative_point.z = point.z;
	relative_point.w = point.w;
	return (relative_point);
}

t_segment_d	transform_camera_relative_segment(t_segment_d segment,
		t_camera *camera)
{
	segment.point_a = transform_camera_relative_point(segment.point_a, camera);
	segment.point_b = transform_camera_relative_point(segment.point_b, camera);
	return (segment);
}

t_vector4d	reverse_transform_camera_relative_point(t_vector4d relative_point,
		t_camera *camera)
{
	t_vector4d	point;
	double		det;
	double		inv_det;

	det = camera->dir.x * camera->dir.x + camera->dir.y * camera->dir.y;
	assert(det != 0);
	inv_det = 1.0 / det;
	point.x = inv_det * (camera->dir.y * relative_point.x + camera->dir.x
			* relative_point.y);
	point.y = inv_det * (camera->dir.y * relative_point.y - camera->dir.x
			* relative_point.x);
	point.z = relative_point.z;
	point.w = relative_point.w;
	point.vec = point.vec + camera->pos.vec;
	return (point);
}
