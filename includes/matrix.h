/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:41:27 by motero            #+#    #+#             */
/*   Updated: 2023/12/03 21:03:53 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "structures.h"
# include "libft.h"

/*############################################################################*/
/*                      VECTOR MATRIX CONVERSIONS                             */
/*############################################################################*/
t_vector4d	point2d_to_vector4d(t_point2d *point);
t_vector4d	point2i_to_vector4d(t_point2i *point);
t_point2d	vector4d_to_point2d(t_vector4d *vec4d);

/*############################################################################*/
/*                              MATRIX OPERATIONS                             */
/*############################################################################*/
t_matrix3x3	matrix_multiply(t_matrix3x3 A, t_matrix3x3 B);
t_matrix3x3	identity_matrix(void);
double		determinant(t_matrix3x3 matrix);
int			invert_matrix(t_matrix3x3 matrix, t_matrix3x3 *inverse);
t_point2d	matrix_vector_multiply(t_matrix3x3 matrix, t_point2d point);


/*############################################################################*/
/*                              MATRIX TRANSFORMATIONS                        */
/*############################################################################*/
t_matrix3x3	rotation_matrix(double theta);
t_matrix3x3	scaling_matrix(t_point2d scale);
t_matrix3x3	translation_matrix(t_point2d translation);
int			push_matrix_op(t_list **matrix_op, t_matrix3x3 matrix);

/*############################################################################*/
/*                              POINTS TRANSFORMATIONS                        */
/*############################################################################*/
t_point2d	transform_point_by_matrix(t_point2i point, t_matrix3x3 matrix);
t_vector4d	transform_homogenous_point_by_matrix(t_vector4d point,
				t_matrix3x3 matrix);
t_point2d	apply_transformations_to_point(t_point2i point,
				t_list *matrix_list);
t_matrix3x3	get_inverse_transformation_matrix(t_matrix3x3 matrix);
t_point2i	back_transform_point_by_matrix(t_vector4d point,
				t_matrix3x3 matrix);

#endif /* MATRIX_H */
