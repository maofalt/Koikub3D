/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:14:34 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:14:47 by olimarti         ###   ########.fr       */
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
