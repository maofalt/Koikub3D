/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:41:27 by motero            #+#    #+#             */
/*   Updated: 2023/11/14 01:36:30 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "structures.h"
# include "libft.h"

/*############################################################################*/
/*                              MATRIX OPERATIONS                             */
/*############################################################################*/
t_matrix3x3	matrix_multiply(t_matrix3x3 A, t_matrix3x3 B);
t_matrix3x3	identity_matrix(void);
t_point2d	matrix_vector_multiply(t_matrix3x3 matrix, t_point2d point);


/*############################################################################*/
/*                              MATRIX TRANSFORMATIONS                        */
/*############################################################################*/
t_matrix3x3	rotation_matrix(double theta);
t_matrix3x3	scaling_matrix(t_point2d scale);
t_matrix3x3	translation_matrix(t_point2d translation);
#endif /* MATRIX_H */
