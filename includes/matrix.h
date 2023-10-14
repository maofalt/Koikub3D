/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_engine.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:41:27 by motero            #+#    #+#             */
/*   Updated: 2023/10/13 22:56:25 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "structures.h"
# include "libft.h"
/*############################################################################*/
/*                              MATRIX STRUCTURES                             */
/*############################################################################*/

typedef double	t_v4d __attribute__((vector_size(4 * sizeof(double))));

typedef union u_vector4d
{
	t_v4d	vec;
	struct {
		double	x;
		double	y;
		double	z;
		double	w;
	};
}	t_vector3d;

typedef struct s_matrix4x4_vectorized
{
	t_vector3d	row[3];
}	t_matrix3x3;

/*############################################################################*/
/*                              MATRIX OPERATIONS                             */
/*############################################################################*/
t_matrix3x3	matrix_multiply(t_matrix3x3 A, t_matrix3x3 B);	
t_matrix3x3	identity_matrix(void);

/*############################################################################*/
/*                              MATRIX TRANSFORMATIONS                        */
/*############################################################################*/
t_matrix3x3	rotation_matrix(double theta);
t_matrix3x3	scaling_matrix(t_point2d scale);
t_matrix3x3	translation_matrix(t_point2d translation);
#endif /* MATRIX_H */