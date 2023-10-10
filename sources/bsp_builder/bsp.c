/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 00:15:03 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/11 01:48:55 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "cub3D.h"
#include "bsp_builder.h"

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
