/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 00:15:03 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/10 18:57:34 by olimarti         ###   ########.fr       */
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


int	cut_space(t_list **segments, t_segment_d *separator, t_list **left, t_list **right)
{
	t_list		*current;
	t_point2d	intersection;
	int			point_a_side;
	int			point_b_side;
	t_segment_d	segment_tmp;
	t_list		*next_tmp;


	*left = NULL;
	*right = NULL;
	current = *segments;
	*segments = NULL;
	while (current != NULL)
	{
		segment_tmp = *(t_segment_d *)current->content;
		point_a_side = point_space_partitioning(separator,
				&segment_tmp.point_a);
		point_b_side = point_space_partitioning(separator,
				&segment_tmp.point_b);
		if ((point_a_side | point_b_side) == 0)
		{
			next_tmp = current->next;
			ft_lstadd_front(segments, current);
			current = next_tmp;
			continue ;
		}
		else if (point_a_side * point_b_side <= 0)
		{
			intersection = find_intersection(*separator, segment_tmp);
			if (point_a_side < 0)
			{
					((t_segment_d*)current->content)->point_b = intersection;
					next_tmp = current->next;
					ft_lstadd_front(left, current);
					current = next_tmp;
			}
			else if (point_a_side > 0)
			{
				((t_segment_d*)current->content)->point_a = intersection;
				((t_segment_d*)current->content)->point_b = segment_tmp.point_a;
				next_tmp = current->next;
				ft_lstadd_front(right, current);
				current = next_tmp;
			}
			if (point_a_side == 0)
			{
				if (point_b_side < 0)
				{
					((t_segment_d*)current->content)->point_a = segment_tmp.point_b;
					((t_segment_d*)current->content)->point_b = intersection;
					next_tmp = current->next;
					ft_lstadd_front(left, current);
					current = next_tmp;
				}
				else if (point_b_side > 0)
				{
					((t_segment_d*)current->content)->point_a = intersection;
					next_tmp = current->next;
					ft_lstadd_front(right, current);
					current = next_tmp;
				}
			}
			else
			{
				if (point_b_side < 0)
				{
					if (add_segment_to_lst(left, (t_segment_d){segment_tmp.point_b, intersection}))
						return (1);
				}
				else if (point_b_side > 0)
				{
					if (add_segment_to_lst(right, (t_segment_d){intersection, segment_tmp.point_b}))
						return (1);
				}
			}
		}
		else
		{
			next_tmp = current->next;
			if (point_a_side < 0 || point_b_side < 0)
				ft_lstadd_front(left, current);
			else
				ft_lstadd_front(right, current);
			current = next_tmp;
		}
	}
	return (0);
}



void	construct_bsp(t_list **segments, t_list **left, t_list **right)
{
	// t_list *left = NULL;
	// t_list *right = NULL;
	// t_segment_d *segment = ((t_segment_d*)(*segments)->content);
	t_list *ptr1;
	t_list *ptr2;

	ptr1 = *segments;
	ptr2 = *segments;

	while (ptr1->next != NULL && ptr1->next->next != NULL)
	{
		ptr2 = ptr2->next;
		ptr1 = ptr1->next->next;
	}

	t_segment_d separator =  *(t_segment_d*)ptr2->content; //{{{20,0}}, {{40,3}}};
	// printf("***%p\n", (t_segment_d*)ptr2->next->content);
	// printf("{%f, %f}{%f, %f}\n", separator.point_a.x,separator.point_a.y,separator.point_b.x,separator.point_b.y);
	cut_space(segments, &separator, left, right);
	// separator = *(t_segment_d*)(ptr2->next->content); //{{{20,0}}, {{40,3}}};
	// printf(";;;%p\n", (t_segment_d*)ptr2->content);
	// printf("-----{%f, %f}{%f, %f}\n", separator.point_a.x,separator.point_a.y,separator.point_b.x,separator.point_b.y);

	// *result = right;
}
