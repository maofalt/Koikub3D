/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_tree_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:37:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:44:55 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures_utils.h"
#include "structures.h"

void	destroy_segment_tree_node(t_tree_node	*node)
{
	t_bsp_tree_node_data	*data;

	if (node == NULL)
		return ;
	data = node->data;
	printf("destroy seg %p\n", node->data);
	if (data && data->sector_segments)
	{
		printf("destroy sector seg\n");
		ft_lstclear(&data->sector_segments, free);
	}
	destroy_tree_node(node);
}

void	destroy_segment_tree(t_tree_node **tree)
{
	destroy_tree(tree, destroy_segment_tree_node);
}
