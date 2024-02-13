/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:31:00 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/12 01:13:44 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_UTILS_H
# define MATHS_UTILS_H

# include "structures.h"

t_vector4d	point2d_to_vector4d(t_point2d *point);
t_point2d	vector4d_to_point2d(t_vector4d *vec4d);
t_vector4d	point2d_to_vector4d_cpy(t_point2d point);
t_point2d	vector4d_to_point2d_cpy(t_vector4d vec4d);

double		point_space_partitioning(t_segment_d *separator, t_point2d *point);
t_side		point_segment_side(t_segment_d *separator, t_vector4d *point);

t_point2d	find_intersection(t_segment_d line, t_segment_d seg);

double		lerp(double alpha, double start, double end);

double		random_double_xorshift32(void);

#endif
