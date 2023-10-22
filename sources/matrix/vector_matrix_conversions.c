/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2023/10/13 21:16:51 by motero           ###   ########.fr       */
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

t_point2d	vector4d_to_point2d(t_vector4d *vec4d)
{
	t_point2d	point2d;

	point2d.x = vec4d->x;
	point2d.y = vec4d->y;
	return (point2d);
}