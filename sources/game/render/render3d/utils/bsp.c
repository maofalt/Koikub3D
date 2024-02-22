/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 14:20:25 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/28 14:20:27 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_utils.h"
#include "structures.h"

t_tree_node	*bsp_search_point(t_tree_node *tree, t_point2d point)
{
	t_tree_node	*child;
	t_segment_d	separator;
	double		point_side;

	if (!tree)
		return (NULL);
	if (!tree->left || !tree->right)
		return (tree);
	separator = ((t_bsp_tree_node_data *)tree->data)->separator;
	point_side = point_space_partitioning(&separator, &point);
	if (point_side > 0)
		child = bsp_search_point(tree->right, point);
	else
		child = bsp_search_point(tree->left, point);
	if (child != NULL)
		return (child);
	return (NULL);
}
