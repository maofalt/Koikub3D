/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 00:15:03 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/09 22:34:29 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "cub3D.h"

int	point_space_partitioning(t_segment_d *separator, t_point2d *point)
{
	t_v2d	ab;
	t_v2d	ap;

	ab = separator->point_b.vec - separator->point_a.vec;
	ap = point->vec - separator->point_a.vec;
	return (ab[0] * ap[1] - ab[1] * ap[0]);
}


int	cut_space(t_list **segments, t_list *separator)
{
	t_list	*current = *segments;
	t_list	*next_tmp;
	t_list	*left = NULL;
	t_list	*right = NULL;
	int		point_a_side;
	int		point_b_side;

	while (current->next != NULL)
	{
		next_tmp = current->next;
		point_a_side = point_space_partitioning(separator,
				&((t_segment_d *)current->next->content)->point_a);
		point_b_side = point_space_partitioning(separator,
				&((t_segment_d *)current->next->content)->point_b);
		if (point_a_side ^ point_b_side)
		{
			//intersection
		}
		else
		{
			ft_lstadd_front(&left, current->next);
			current->next = current->next->next;
		}

	}
}

// void construct_bsp(void)
// {

// }

