/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/16 17:43:36 by motero           ###   ########.fr       */
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
	if ((a->type == MAP || a->type == UI || a->type == GAME)
		&& (b->type == MAP || b->type == UI || b->type == GAME))
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


