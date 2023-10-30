/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cut_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:33:10 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/14 19:04:37 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"

t_point2d	find_intersection(t_segment_d line, t_segment_d seg)
{
	t_point2d	intersection;
	t_point2d	ab_1;
	t_point2d	ab_2;
	double		c1;
	double		c2;

	ab_1 = (t_point2d){{line.point_b.y - line.point_a.y,
		line.point_a.x - line.point_b.x}};
	c1 = ab_1.x * line.point_a.x + ab_1.y * line.point_a.y;
	ab_2 = (t_point2d){{seg.point_b.y - seg.point_a.y,
		seg.point_a.x - seg.point_b.x}};
	c2 = ab_2.x * seg.point_a.x + ab_2.y * seg.point_a.y;
	intersection.vec = (t_v2d){(ab_2.y * c1 - ab_1.y * c2),
		(ab_1.x * c2 - ab_2.x * c1)};
	intersection.vec /= ab_1.x * ab_2.y - ab_2.x * ab_1.y;
	return (intersection);
}

void	lst_move_node(t_list **list, t_list **node)
{
	t_list	*next_tmp;

	next_tmp = (*node)->next;
	ft_lstadd_front(list, (*node));
	(*node) = next_tmp;
}
