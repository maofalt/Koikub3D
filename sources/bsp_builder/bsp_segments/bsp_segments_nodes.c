/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_segments_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:31:15 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/07 23:31:39 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "structures.h"

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
			ft_lstclear(&bsp_list, free);
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
