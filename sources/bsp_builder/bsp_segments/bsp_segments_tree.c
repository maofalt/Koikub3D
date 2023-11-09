/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_segments_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:29:53 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:50:43 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures_utils.h"
#include "bsp_builder.h"

void	destroy_bsp_segment_tree_node(t_tree_node	*node)
{
	t_bsp_tree_node_data	*data;

	if (node == NULL)
		return ;
	data = node->data;
	if (data && data->sector_segments)
	{
		ft_lstclear(&data->sector_segments, destroy_full_bsp_segment);
	}
	destroy_tree_node(node);
}

void	destroy_bsp_segment_tree(t_tree_node **tree)
{
	destroy_tree(tree, destroy_bsp_segment_tree_node);
}
