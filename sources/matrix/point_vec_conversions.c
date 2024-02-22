/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_vec_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:18:59 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 19:20:43 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

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
