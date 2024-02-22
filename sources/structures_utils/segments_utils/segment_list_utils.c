/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:34:59 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/04 22:14:58 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

t_list	*create_segment_node(void)
{
	t_segment_d	*segment;
	t_list		*node;

	segment = ft_calloc(1, sizeof(t_segment_d));
	if (segment == NULL)
		return (NULL);
	node = ft_lstnew(segment);
	if (node == NULL)
	{
		free(segment);
		return (NULL);
	}
	return (node);
}

t_list	*create_initialized_segment_node(t_segment_d segment)
{
	t_list	*node;

	node = create_segment_node();
	if (node != NULL)
	{
		*(t_segment_d *)node->content = segment;
	}
	return (node);
}

int	add_segment_to_lst(t_list **lst, t_segment_d segment)
{
	t_list	*node;

	node = create_initialized_segment_node(segment);
	if (!node)
		return (1);
	ft_lstadd_front(lst, node);
	return (0);
}

t_list	*duplicate_segment_node(t_list *original_node)
{
	t_segment_d	*original_segment;
	t_segment_d	*duplicated_segment;
	t_list		*duplicated_node;

	if (!original_node || !original_node->content)
		return (NULL);
	original_segment = (t_segment_d *)original_node->content;
	duplicated_segment = ft_calloc(1, sizeof(t_segment_d));
	if (!duplicated_segment)
		return (NULL);
	*duplicated_segment = *original_segment;
	duplicated_node = ft_lstnew(duplicated_segment);
	if (!duplicated_node)
	{
		free(duplicated_segment);
		return (NULL);
	}
	return (duplicated_node);
}

t_list	*lst_segment_cpy(t_list *lst)
{
	t_list	*new_lst;
	t_list	*new_node;
	t_list	*current_node;

	new_lst = NULL;
	current_node = lst;
	while (current_node)
	{
		new_node = duplicate_segment_node(current_node);
		if (!new_node)
			return (ft_lstclear(&new_lst, free), NULL);
		ft_lstadd_back(&new_lst, new_node);
		current_node = current_node->next;
	}
	return (new_lst);
}
