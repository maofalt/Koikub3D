/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 00:15:03 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/10 04:51:25 by olimarti         ###   ########.fr       */
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
	t_list tmp;
	tmp.next = *segments; // TODO remove this hack
	t_list	*current = &tmp;
	t_list	*next_tmp;
	*left = NULL;
	*right = NULL;
	int		point_a_side;
	int		point_b_side;
	t_point2d intersection;
	t_segment_d	segment_tmp;
	while (current->next != NULL)
	{
		segment_tmp = *(t_segment_d *)current->next->content;
		point_a_side = point_space_partitioning(separator,
				&segment_tmp.point_a);
		point_b_side = point_space_partitioning(separator,
				&segment_tmp.point_b);
		if (point_a_side * point_b_side < 0)
		{
			//intersection should cut segment

			intersection = find_intersection(*separator, segment_tmp);
			if (point_a_side < 0)
			{
					// ((t_segment_d*)current->next->content)->point_a = ((t_segment_d*)current->next->content)->point_a;
					((t_segment_d*)current->next->content)->point_b = intersection;
					next_tmp = current->next->next;
					ft_lstadd_front(left, current->next);
					current->next = next_tmp;
				// add_segment_to_lst(left, (t_segment_d){((t_segment_d *)current->next->content)->point_a, intersection});
			} else if (point_a_side > 0)
			{
				((t_segment_d*)current->next->content)->point_a = intersection;
				((t_segment_d*)current->next->content)->point_b = segment_tmp.point_a;
				next_tmp = current->next->next;
				ft_lstadd_front(right, current->next);
					current->next = next_tmp;
				// add_segment_to_lst(right, (t_segment_d){intersection, ((t_segment_d *)current->next->content)->point_a});
			}
			if (point_a_side == 0)
			{
				if (point_b_side < 0)
				{
					((t_segment_d*)current->next->content)->point_a = segment_tmp.point_b;
					((t_segment_d*)current->next->content)->point_b = intersection;
					next_tmp = current->next->next;
					ft_lstadd_front(left, current->next);
					current->next = next_tmp;
					//add_segment_to_lst(left, (t_segment_d){((t_segment_d *)current->next->content)->point_b, intersection});
				}
				else if (point_b_side > 0)
				{
					((t_segment_d*)current->next->content)->point_a = intersection;
					next_tmp = current->next->next;
					ft_lstadd_front(right, current->next);
					current->next = next_tmp;
					// add_segment_to_lst(right, (t_segment_d){intersection, ((t_segment_d *)current->next->content)->point_b});
				}
			}
			else
			{
				if (point_b_side < 0)
				{
					add_segment_to_lst(left, (t_segment_d){segment_tmp.point_b, intersection});
				}
				else if (point_b_side > 0)
				{
					add_segment_to_lst(right, (t_segment_d){intersection, segment_tmp.point_b});
				}
			}
			// else
			// {
			// 	current = current->next; //maybe free
			// }
			printf("%d, %d, (%f, %f, (%f, %f\n", point_a_side, point_b_side, segment_tmp.point_a.x, segment_tmp.point_a.y, segment_tmp.point_b.x, segment_tmp.point_b.y);
		}
		else
		{
			next_tmp = current->next->next;
			if (point_a_side < 0 || point_b_side < 0)
				ft_lstadd_front(left, current->next);
			else if (point_a_side > 0 || point_b_side > 0)
				ft_lstadd_front(right, current->next);
			else
				printf("------\n");
			current->next = next_tmp;
		}
	}
	return (0);
}

void construct_bsp(t_list **segments, t_list **left, t_list **right)
{
	// t_list *left = NULL;
	// t_list *right = NULL;
	// t_segment_d *segment = ((t_segment_d*)(*segments)->content);
	t_segment_d separator = {{{20,0}}, {{40,3}}};
	cut_space(segments, &separator, left, right);
	// *result = right;
}

// int main() {
// 	t_point2d p1 = {.vec={0, 0}};
// 	t_point2d p2 = {.vec={3, 5}};
// 	t_segment_d seg = {{.vec={-4, -2}}, {.vec={2, 0.5}}};
// 	t_point2d intersection;

// 	intersection = findIntersection(p1, p2, seg);
// 	printf("Intersection at (%lf, %lf)\n", intersection.x, intersection.y);

// 	return 0;
// }
