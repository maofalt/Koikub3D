/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:26:10 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:58:02 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures_utils.h"

t_tree_node	*create_tree_node(void)
{
	t_tree_node				*tree_node;
	t_bsp_tree_node_data	*tree_data;

	tree_node = malloc(sizeof(t_tree_node));
	tree_data = ft_calloc(1, sizeof(t_bsp_tree_node_data));
	if (tree_node == NULL || tree_data == NULL)
	{
		free(tree_data);
		free(tree_node);
		return (NULL);
	}
	tree_node->left = NULL;
	tree_node->right = NULL;
	tree_node->parent = NULL;
	tree_node->data = tree_data;
	return (tree_node);
}

void	destroy_tree_node(t_tree_node	*node)
{
	if (node == NULL)
		return ;
	free(node->data);
	free(node);
}

void	destroy_tree(t_tree_node **tree, void (*del)(t_tree_node *))
{
	if (tree == NULL || *tree == NULL)
		return ;
	destroy_tree(&(*tree)->left, del);
	destroy_tree(&(*tree)->right, del);
	if (del)
		del(*tree);
	*tree = NULL;
}
