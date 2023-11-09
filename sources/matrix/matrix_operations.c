/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2023/10/19 00:57:39 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix3x3	matrix_multiply(t_matrix3x3 A, t_matrix3x3 B)
{
	t_matrix3x3	result;
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			result.row[i].vec[j] = 0;
			k = 0;
			while (k < 3)
			{
				result.row[i].vec[j] += A.row[i].vec[k] * B.row[k].vec[j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

t_matrix3x3	identity_matrix(void)
{
	t_matrix3x3	identity;
	int			i;
	int			j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (i == j)
				identity.row[i].vec[j] = 1.0;
			else
				identity.row[i].vec[j] = 0.0;
			j++;
		}
		i++;
	}
	return (identity);
}


t_point2d	matrix_vector_multiply(t_matrix3x3 matrix, t_point2d point)
{
	t_point2d	result;

	result.x = matrix.row[0].x * point.x
		+ matrix.row[0].y * point.y + matrix.row[0].z;
	result.y = matrix.row[1].x * point.x
		+ matrix.row[1].y * point.y + matrix.row[1].z;

	return (result);
}
