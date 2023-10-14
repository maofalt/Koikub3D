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
