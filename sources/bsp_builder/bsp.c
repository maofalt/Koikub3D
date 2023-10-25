/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 00:15:03 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/25 23:51:33 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "cub3D.h"
#include "bsp_builder.h"

// void	construct_bsp(t_list **segments, t_list **left, t_list **right)
// {
// 	// t_list *left = NULL;
// 	// t_list *right = NULL;
// 	// t_segment_d *segment = ((t_segment_d*)(*segments)->content);
// 	t_list *ptr1;
// 	t_list *ptr2;

// 	ptr1 = *segments;
// 	ptr2 = *segments;

// 	while (ptr1->next != NULL && ptr1->next->next != NULL)
// 	{
// 		ptr2 = ptr2->next;
// 		ptr1 = ptr1->next->next;
// 	}

// 	t_segment_d separator =  *(t_segment_d*)ptr2->content; //{{{20,0}}, {{40,3}}};
// 	// printf("***%p\n", (t_segment_d*)ptr2->next->content);
// 	// printf("{%f, %f}{%f, %f}\n", separator.point_a.x,separator.point_a.y,separator.point_b.x,separator.point_b.y);
// 	cut_space(segments, &separator, left, right);
// 	// separator = *(t_segment_d*)(ptr2->next->content); //{{{20,0}}, {{40,3}}};
// 	// printf(";;;%p\n", (t_segment_d*)ptr2->content);
// 	// printf("-----{%f, %f}{%f, %f}\n", separator.point_a.x,separator.point_a.y,separator.point_b.x,separator.point_b.y);

// 	// *result = right;
// }


t_list	*choose_separator(t_list *segments)
{
	t_list	*ptr1;
	t_list	*ptr2;

	ptr1 = segments;
	ptr2 = segments;
	if (segments == NULL)
		return (NULL);
	while (ptr1->next != NULL && ptr1->next->next != NULL)
	{
		ptr2 = ptr2->next;
		ptr1 = ptr1->next->next;
	}
	return (ptr2);
}





// int	cut_space(
// 	t_list **segments,
// 	t_segment_d *separator,
// 	t_list **left,
// 	t_list **right)

// int construct_bsp(t_list **segments, t_tree_node **tree, t_cub *data)
// {
// 	const t_list			*separator_node = choose_separator(*segments);
// 	t_list					*left;
// 	t_list					*right;
// 	t_bsp_tree_node_data	*node_data;
// 	t_tree_node				*node;

// 	if (separator_node == NULL)
// 		return (0);
// 	left = NULL;
// 	right = NULL;
// 	if (cut_space(segments, separator_node->content, &left, &right))
// 		return (1);//error
// 	node = malloc(sizeof(t_tree_node));
// 	node_data = malloc(sizeof(t_bsp_tree_node_data));
// 	if (!node_data)
// 		return (1); //todo protect (free)
// 	node_data->separator = separator_node->content;
// 	node_data->sector_data.floor_height = 0;
// 	node->left = NULL;
// 	node->right = NULL;
// 	node->parent = NULL;
// 	node->data = node_data;
// 	*tree = node;
// 	// draw_map_segments(data, *segments);
// 	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
// 		// data->screen.mlx_img, 0, 0);
// 	// usleep(100000);
// 	// mlx_do_sync(data->mlx_ptr);
// 	if (construct_bsp(&left, &node->left, data))
// 		return (1); //todo free
// 	if (node->left)
// 		node->left->parent = node;
// 	if (construct_bsp(&right, &node->right, data))
// 		return (1);
// 	if (node->right)
// 		node->right->parent = node;
// 	return (0);
// }

static int	segment_is_horizontal(t_segment_d *segment)
{
	return (segment->point_a.x == segment->point_b.x);
}


int construct_bsp(t_list **unprocessed_segments, t_list **processed_segments , t_tree_node **tree)
{
	const t_list			*separator_node = choose_separator(*unprocessed_segments);
	t_list					*left;
	t_list					*right;
	t_bsp_tree_node_data	*node_data;
	t_tree_node				*node;

	if (separator_node == NULL)
	{

		node = malloc(sizeof(t_tree_node));
		node_data = malloc(sizeof(t_bsp_tree_node_data));
		if (!node_data)
			return (1); //Todo protect (free)
		// node_data->separator = NULL;
		node_data->sector_data.floor_height = 0;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->data = node_data;
		*tree = node;
		node_data->sector_segments = *processed_segments;



		return (0);
	}
	left = NULL;
	right = NULL;

	//-----------------
	t_list	*processed_segments_left;
	t_list	*processed_segments_right;

	processed_segments_left = NULL;
	processed_segments_right = NULL;
	if (cut_space(unprocessed_segments, separator_node->content, &left, &right))
		return (1);//TODO Error
	detect_gap(*unprocessed_segments, !segment_is_horizontal(separator_node->content));
	if (cut_space(processed_segments, separator_node->content, &processed_segments_left, &processed_segments_right))
		return (1);//TODO Error
	detect_gap(*unprocessed_segments, !segment_is_horizontal(separator_node->content));

	while (*unprocessed_segments)
	{
		if (add_segment_to_lst(&processed_segments_left, *(t_segment_d *)(*unprocessed_segments)->content))
			return (1); //TODO Correct error management
		lst_move_node(&processed_segments_right, unprocessed_segments);
	}


	//-----------------

	node = malloc(sizeof(t_tree_node));
	node_data = malloc(sizeof(t_bsp_tree_node_data));
	if (!node_data)
		return (1); //Todo protect (free)
	node_data->separator = *(t_segment_d *)separator_node->content;
	node_data->sector_data.floor_height = 0;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->data = node_data;
	*tree = node;
	// draw_map_segments(data, *segments);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		// data->screen.mlx_img, 0, 0);
	// usleep(100000);
	// mlx_do_sync(data->mlx_ptr);
	if (construct_bsp(&left, &processed_segments_left ,&node->left))
		return (1); //todo free
	if (node->left)
		node->left->parent = node;
	if (construct_bsp(&right, &processed_segments_right, &node->right))
		return (1);
	if (node->right)
		node->right->parent = node;
	return (0);
}

