/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:54:15 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:57:08 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "structures_utils.h"

static int	_handle_map_cut_error(t_list **bsp_segments,
		t_list **left, t_list **right)
{
	ft_lstclear(bsp_segments, destroy_full_bsp_segment);
	ft_lstclear(left, destroy_full_bsp_segment);
	ft_lstclear(right, destroy_full_bsp_segment);
	perror("error: _recursive_map_cut\n");
	return (1);
}

int	_recursive_map_cut_create_leaf(t_list **bsp_segments, t_tree_node **tree)
{
	t_tree_node		*tree_node;

	tree_node = create_tree_node();
	if (tree_node == NULL)
		return (1);
	((t_bsp_tree_node_data *)tree_node->data)->sector_data.floor_height = 0;
	((t_bsp_tree_node_data *)tree_node->data)
		->sector_segments = *bsp_segments;
	*tree = tree_node;
	return (0);
}
int	_recursive_map_cut(t_list **bsp_segments, t_tree_node **tree);

static int	_recursive_map_add_node(
	t_tree_node **tree,
	t_list *left,
	t_list *right,
	t_bsp_segment *separator
	)
{
	t_tree_node		*tree_node;

	tree_node = create_tree_node();
	if (tree_node == NULL)
		return (1);
	((t_bsp_tree_node_data *)tree_node->data)->sector_data.floor_height = 0;
	((t_bsp_tree_node_data *)tree_node->data)->separator = *separator->segment;
	if (_recursive_map_cut(&left, &(tree_node->left))
		|| _recursive_map_cut(&right, &(tree_node->right)))
	{
		destroy_bsp_segment_tree(&tree_node);
		return (1);
	}
	if (tree_node->left)
		tree_node->left->parent = tree_node;
	if (tree_node->right)
		tree_node->right->parent = tree_node;
	*tree = tree_node;
	return (0);
}

int	_recursive_map_cut(t_list **bsp_segments, t_tree_node **tree)
{
	t_list			*separator_node;
	t_bsp_segment	*separator;
	t_list			*left;
	t_list			*right;

	left = NULL;
	right = NULL;
	if (tree == NULL)
		return (0);
	separator_node = choose_separator(*bsp_segments);
	if (separator_node == NULL)
		return (_recursive_map_cut_create_leaf(bsp_segments, tree));
	separator = separator_node->content;
	separator->used_as_separator = 1;
	compute_bsp_segments_intersections(*bsp_segments, separator->segment);
	if (create_portals(*bsp_segments, separator->segment, bsp_segments))
		return (_handle_map_cut_error(bsp_segments, &left, &right), 1);
	if (map_cut(bsp_segments, &left, &right))
		return (_handle_map_cut_error(bsp_segments, &left, &right), 1);
	if (_recursive_map_add_node(tree, left, right, separator))
		return (_handle_map_cut_error(bsp_segments, &left, &right), 1);
	return (0);
}

int	construct_bsp(t_list **segments, t_tree_node **tree)
{
	t_list		*converted_segments;
	t_tree_node	*bsp_tree;

	bsp_tree = NULL;
	converted_segments = convert_to_bsp_segments(*segments);
	if (converted_segments == NULL)
		return (1);
	if (_recursive_map_cut(&converted_segments, &bsp_tree))
	{
		ft_lstclear(&converted_segments, destroy_full_bsp_segment);
		perror("error: construct_bsp");
		*tree = NULL;
		return (1);
	}
	tree_update_portals_links_to_segments(bsp_tree);
	tree_convert_bsp_segment_to_segments(bsp_tree);
	*tree = bsp_tree;
	return (0);
}
