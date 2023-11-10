/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:34:59 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:35:03 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

t_list	*create_segment_node(void)
{
	t_segment_d	*segment;
	t_list		*node;

	segment = malloc(sizeof(t_segment_d));
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