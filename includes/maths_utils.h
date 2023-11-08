/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:31:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:02:38 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

t_vector4d	point2d_to_vector4d(t_point2d *point);
t_point2d	vector4d_to_point2d(t_vector4d *vec4d);
t_vector4d	point2d_to_vector4d_cpy(t_point2d point);
t_point2d	vector4d_to_point2d_cpy(t_vector4d vec4d);

double		point_space_partitioning(t_segment_d *separator, t_point2d *point);
t_point2d	find_intersection(t_segment_d line, t_segment_d seg);


#endif
