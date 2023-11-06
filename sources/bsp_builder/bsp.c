/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:54:15 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/05 21:41:31 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"


static t_list	*_get_next_separator(t_list *bsp_segments_lst)
{
	t_bsp_segment	*segment;

	if (bsp_segments_lst == NULL)
		return (NULL);
	segment = bsp_segments_lst->content;
	while (bsp_segments_lst != NULL && segment->used_as_separator != 0)
	{
		bsp_segments_lst = bsp_segments_lst->next;
		if (bsp_segments_lst != NULL)
			segment = bsp_segments_lst->content;
	}
	return (bsp_segments_lst);
}


t_list	*choose_separator(t_list *bsp_segments)
{
	t_list	*ptr1;
	t_list	*ptr2;

	bsp_segments = _get_next_separator(bsp_segments);
	if (bsp_segments == NULL)
		return (NULL);
	ptr1 = bsp_segments;
	ptr2 = bsp_segments;
	while (ptr1 != NULL)
	{
		ptr1 = _get_next_separator(ptr1->next);
		if (ptr1)
			ptr1 = _get_next_separator(ptr1->next);
		if (ptr1 && ptr2)
			ptr2 = _get_next_separator(ptr2->next);
	}
	return (ptr2);
}

void	compute_segments_intersections(
		t_list *bsp_segments,
		t_segment_d *separator
		)
{
	t_bsp_segment	*segment;

	while (bsp_segments != NULL)
	{
		segment = bsp_segments->content;
		bsp_segment_compute_intersec(segment, separator);
		bsp_segments = bsp_segments->next;
	}
}

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
		perror("create_tree_node");
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

void	destroy_segment_tree_node(t_tree_node	*node)
{
	t_bsp_tree_node_data *data;
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

void	destroy_bsp_segment_tree_node(t_tree_node	*node)
{
	t_bsp_tree_node_data *data;
	if (node == NULL)
		return ;

	data = node->data;
	if (data && data->sector_segments)
	{
		ft_lstclear(&data->sector_segments, (void (*)(void *))destroy_full_bsp_segment);
	}
	destroy_tree_node(node);
}

int	_recursive_map_cut(t_list **bsp_segments, t_tree_node **tree)
{
	t_list			*separator_node;
	t_bsp_segment	*separator;
	t_list			*left;
	t_list			*right;
	t_tree_node		*tree_node;

	left = NULL;
	right = NULL;

	if (tree == NULL)
		return (0);
	separator_node = choose_separator(*bsp_segments);
	if (separator_node == NULL)
	{
		tree_node = create_tree_node();
		if (tree_node == NULL)
			return (1);
		((t_bsp_tree_node_data *)tree_node->data)->sector_data.floor_height = 0;
		((t_bsp_tree_node_data *)tree_node->data)
			->sector_segments = *bsp_segments;
		*tree = tree_node;
		return (0);
	}

	separator = separator_node->content;
	separator->used_as_separator = 1;
	compute_segments_intersections(*bsp_segments, separator->segment);
	//create_portals
	create_portals(*bsp_segments, (separator->segment->point_a.x == separator->segment->point_b.x), bsp_segments); //TODO: move horizontal check inside

	//map_cut
	if (map_cut(bsp_segments, &left, &right))
	{
		//error;
		//TODO: free Left right
		puts("map cut gone wrong\n");

		return (1);
	}


	//TODO: protect mallocs
	tree_node = create_tree_node();
	if (tree_node == NULL)
		//TODO: free Left right
		return (1);
	((t_bsp_tree_node_data *)tree_node->data)->sector_data.floor_height = 0;
	((t_bsp_tree_node_data *)tree_node->data)->separator = *separator->segment;
	// *tree = tree_node;

	if (_recursive_map_cut(&left, &(tree_node->left))
		|| _recursive_map_cut(&right, &(tree_node->right)))
	{
		perror("error: _recursive_map_cut");
		//TODO: error
		//TODO: free Left right Tree Node
	}
	if (tree_node->left)
		tree_node->left->parent = tree_node;
	if (tree_node->right)
		tree_node->right->parent = tree_node;
	*tree = tree_node;

	return (0);
}


void	lst_convert_and_free_bsp_segments(t_list **bsp_list)
{
	t_list			*current;
	t_bsp_segment	*bsp_seg;

	current = *bsp_list;
	while (current != NULL)
	{
		bsp_seg = (t_bsp_segment *)current->content;
		current->content = bsp_seg->segment;
		free(bsp_seg);
		current = current->next;
	}
}

void	tree_convert_bsp_segment_to_segments(t_tree_node *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left == NULL && tree->right == NULL)
	{
		lst_convert_and_free_bsp_segments(
			&((t_bsp_tree_node_data*)tree->data)->sector_segments);
		return ;
	}

	tree_convert_bsp_segment_to_segments(tree->left);
	tree_convert_bsp_segment_to_segments(tree->right);
}

void	lst_update_portals_links_to_segments(t_list **bsp_list)
{
	t_list			*current;
	t_bsp_segment	*bsp_seg;

	current = *bsp_list;
	while (current != NULL)
	{
		bsp_seg = (t_bsp_segment *)current->content;
		if (bsp_seg->segment->data.type == PORTAL)
		{
			bsp_seg->segment->data.data.portal.destination = ((t_bsp_segment *)
					bsp_seg->segment->data.data.portal.destination)->segment;
		}
		current = current->next;
	}
}

void	tree_update_portals_links_to_segments(t_tree_node *tree)
{
	if (tree->left == NULL && tree->right == NULL)
	{
		lst_update_portals_links_to_segments(
			&((t_bsp_tree_node_data*)tree->data)->sector_segments);
		return ;
	}

	tree_update_portals_links_to_segments(tree->left);
	tree_update_portals_links_to_segments(tree->right);
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
		//TODO: free tree and converted seg
		puts("recursive map cut gone wrong\n");
	}
	tree_update_portals_links_to_segments(bsp_tree);
	tree_convert_bsp_segment_to_segments(bsp_tree);
	*tree = bsp_tree;
	return (0);
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


void	destroy_bsp_segment_tree(t_tree_node **tree)
{
	destroy_tree(tree, destroy_bsp_segment_tree_node);
}

void	destroy_segment_tree(t_tree_node **tree)
{
	destroy_tree(tree, destroy_segment_tree_node);
}
