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

double	determinant(t_matrix3x3 matrix)
{
	return (matrix.row[0].x
		* (matrix.row[1].y * matrix.row[2].z
			- matrix.row[1].z * matrix.row[2].y)
		- matrix.row[0].y * (matrix.row[1].x * matrix.row[2].z
			- matrix.row[1].z * matrix.row[2].x)
		+ matrix.row[0].z * (matrix.row[1].x * matrix.row[2].y
			- matrix.row[1].y * matrix.row[2].x));
}

int	invert_matrix(t_matrix3x3 matrix, t_matrix3x3 *inverse)
{
	const double	det = determinant(matrix);

	if (fabs(det) < 1e-6)
		return (printf("Matrix is singular, can't find its inverse.\n"),
			1);
	inverse->row[0].x = (matrix.row[1].y * matrix.row[2].z
			- matrix.row[2].y * matrix.row[1].z) / det;
	inverse->row[0].y = -(matrix.row[0].y * matrix.row[2].z
			- matrix.row[2].y * matrix.row[0].z) / det;
	inverse->row[0].z = (matrix.row[0].y * matrix.row[1].z
			- matrix.row[1].y * matrix.row[0].z) / det;
	inverse->row[1].x = -(matrix.row[1].x * matrix.row[2].z
			- matrix.row[2].x * matrix.row[1].z) / det;
	inverse->row[1].y = (matrix.row[0].x * matrix.row[2].z
			- matrix.row[2].x * matrix.row[0].z) / det;
	inverse->row[1].z = -(matrix.row[0].x * matrix.row[1].z
			- matrix.row[1].x * matrix.row[0].z) / det;
	inverse->row[2].x = (matrix.row[1].x * matrix.row[2].y
			- matrix.row[2].x * matrix.row[1].y) / det;
	inverse->row[2].y = -(matrix.row[0].x * matrix.row[2].y
			- matrix.row[2].x * matrix.row[0].y) / det;
	inverse->row[2].z = (matrix.row[0].x * matrix.row[1].y
			- matrix.row[1].x * matrix.row[0].y) / det;
	return (0);
}
