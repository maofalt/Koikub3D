/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:30:12 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/07 21:38:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "structures.h"

t_bsp_segment	*create_bsp_segment(t_segment_d *segment)
{
	t_bsp_segment	*bsp_seg;

	bsp_seg = malloc(sizeof(t_bsp_segment));
	if (!bsp_seg)
	{
		return (NULL);
	}
	bsp_seg->segment = segment;
	bsp_seg->used_as_separator = 0;
	bsp_seg->side_of_separator = SIDE_ON;
	bsp_seg->point_a_side = SIDE_ON;
	bsp_seg->point_b_side = SIDE_ON;
	bsp_seg->separator_intersection = (t_point2d){{0}};
	bsp_seg->has_separator_intersection = 0;
	bsp_seg->node_ptr = NULL;
	return (bsp_seg);
}

void	destroy_bsp_segment(void *bsp_seg)
{
	free(bsp_seg);
}

void	destroy_full_bsp_segment(void *bsp_seg)
{
	if (bsp_seg)
	{
		free(((t_bsp_segment *)bsp_seg)->segment);
		free(bsp_seg);
	}
}


static t_bsp_segment	*init_new_bsp_segment(void)
{
	t_bsp_segment	*bsp_seg;
	t_segment_d		*seg;

	bsp_seg = malloc(sizeof(t_bsp_segment));
	if (!bsp_seg)
		return (NULL);
	seg = malloc(sizeof(t_segment_d));
	if (!seg)
	{
		free(bsp_seg);
		return (NULL);
	}
	bsp_seg->segment = seg;
	bsp_seg->used_as_separator = 0;
	bsp_seg->side_of_separator = SIDE_ON;
	bsp_seg->point_a_side = SIDE_ON;
	bsp_seg->point_b_side = SIDE_ON;
	bsp_seg->separator_intersection = (t_point2d){{0}};
	bsp_seg->has_separator_intersection = 0;
	bsp_seg->node_ptr = NULL;
	return (bsp_seg);
}

t_list	*convert_to_bsp_segments(t_list *segment_list)
{
	t_list			*bsp_list;
	t_bsp_segment	*bsp_seg;
	t_list			*new_node;

	bsp_list = NULL;
	while (segment_list)
	{
		new_node = create_bsp_segment_node();
		if (!new_node)
		{
			ft_lstclear(&bsp_list, destroy_bsp_segment);
			return (NULL);
		}
		bsp_seg = new_node->content;
		*bsp_seg->segment = *(t_segment_d *)segment_list->content;
		bsp_seg->node_ptr = new_node;
		ft_lstadd_back(&bsp_list, new_node);
		segment_list = segment_list->next;
	}
	return (bsp_list);
}

t_list	*create_bsp_segment_node(void)
{
	t_list			*node;
	t_bsp_segment	*bsp_seg;

	bsp_seg = init_new_bsp_segment();
	if (!bsp_seg)
		return (NULL);
	node = ft_lstnew(bsp_seg);
	if (!node)
	{
		free(bsp_seg->segment);
		free(bsp_seg);
		return (NULL);
	}
	bsp_seg->node_ptr = node;
	return (node);
}


void	destroy_full_bsp_segment_node(t_list *node)
{
	t_bsp_segment	*bsp_seg;

	if (!node)
		return ;
	bsp_seg = (t_bsp_segment *)node->content;
	if (bsp_seg)
	{
		free(bsp_seg->segment);
		free(bsp_seg);
	}
	free(node);
}

t_bsp_segment	*duplicate_bsp_segment(t_bsp_segment *original)
{
	t_bsp_segment	*dup;
	t_segment_d		*seg_dup;

	if (!original)
		return (NULL);
	dup = malloc(sizeof(t_bsp_segment));
	if (!dup)
		return (NULL);
	seg_dup = malloc(sizeof(t_segment_d));
	if (!seg_dup)
	{
		free(dup);
		return (NULL);
	}
	*seg_dup = *(original->segment);
	dup->segment = seg_dup;
	dup->used_as_separator = original->used_as_separator;
	dup->side_of_separator = original->side_of_separator;
	dup->point_a_side = original->point_a_side;
	dup->point_b_side = original->point_b_side;
	dup->separator_intersection = original->separator_intersection;
	dup->has_separator_intersection = original->has_separator_intersection;
	dup->node_ptr = original->node_ptr;
	return (dup);
}


t_list	*duplicate_bsp_segment_node(t_list *original_node)
{
	t_bsp_segment	*original_bsp;
	t_bsp_segment	*duplicated_bsp;
	t_list			*duplicated_node;

	if (!original_node || !original_node->content)
		return (NULL);
	original_bsp = (t_bsp_segment *)original_node->content;
	duplicated_bsp = duplicate_bsp_segment(original_bsp);
	if (!duplicated_bsp)
		return (NULL);
	duplicated_node = ft_lstnew(duplicated_bsp);
	if (!duplicated_node)
	{
		free(duplicated_bsp->segment);
		free(duplicated_bsp);
		return (NULL);
	}
	duplicated_bsp->node_ptr = duplicated_node;
	return (duplicated_node);
}
