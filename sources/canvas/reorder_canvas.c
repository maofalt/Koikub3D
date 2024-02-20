/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder_canvas.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 20:28:01 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

void	reorder_canvases_by_z_index(t_list **canvas_list)
{
	t_list		*current;
	t_list		*index;
	t_canvas	*current_canvas;
	t_canvas	*index_canvas;

	current = *canvas_list;
	while (current)
	{
		index = current->next;
		while (index)
		{
			current_canvas = (t_canvas *)current->content;
			index_canvas = (t_canvas *)index->content;
			if (should_swap(current_canvas, index_canvas))
				swap_canvas_content(current, index);
			index = index->next;
		}
		current = current->next;
	}
}

bool	should_swap(t_canvas *a, t_canvas *b)
{
	if ((is_valid_canvas(a) && is_valid_canvas(b)))
		return (a->z_index > b->z_index);
	return (false);
}

void	swap_canvas_content(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}
