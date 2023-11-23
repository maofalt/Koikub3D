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

t_list	*initialize_canvas_and_add_to_list(t_point2i size,
			t_canvas_type type,
			t_list **canvas_list)
{
	t_canvas	*canvas;
	t_list		*new_node;

	canvas = initialize_single_canvas(size, type);
	if (!canvas)
		return (NULL);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (free_canvas(canvas), NULL);
	new_node->content = canvas;
	ft_lstadd_back(canvas_list, new_node);
	//new_node->next = *canvas_list;
	//*canvas_list = new_node;
	return (new_node);
}

void	free_canvas_list(t_list *canvas_list)
{
	t_list	*current_node;
	t_list	*next_node;

	current_node = canvas_list;
	while (current_node)
	{
		next_node = current_node->next;
		free_canvas((t_canvas *)current_node->content);
		free(current_node);
		current_node = next_node;
	}
	current_node = NULL;
}

t_list	*initialize_canvas_list(t_modus_state state,
	t_setup_by_game_state *canvas_setups)
{
	t_canvas_init_entry			*canvas_init_table;
	t_list						*canvas_list;
	t_list						*new_node;
	size_t						i;

	canvas_init_table = NULL;
	canvas_init_table = get_canvas_init_table(state, canvas_setups);
	printf("canvas_init_table: %p\n", canvas_init_table);
	if (!canvas_init_table)
		return (NULL);
	canvas_list = NULL;
	i = 0;
	while (i < canvas_setups->canvas_count)
	{
		new_node = initialize_canvas_and_add_to_list(canvas_init_table[i].size,
				canvas_init_table[i].type,
				&canvas_list);
		if (!new_node)
			return (free_canvas_list(canvas_list), NULL);
		((t_canvas *)new_node->content)->info = canvas_init_table[i];
		i++;
	}
	//reorder_canvases_by_z_index(&canvas_list);
	return (canvas_list);
}

t_canvas_init_entry	*get_canvas_init_table(t_modus_state state,
	t_setup_by_game_state *canvas_setups)
{
	size_t	i;

	i = 0;
	while (canvas_setups[i].game_state != END_GAME_STATE)
	{
		if (canvas_setups[i].game_state == state)
			return (canvas_setups[i].canvas_configurations);
		i++;
	}
	return (NULL);
}

t_canvas	*get_canvas_from_list(t_list *canvas_list,
	t_canvas_type type)
{
	t_list		*current_node;
	t_canvas	*current_canvas;

	current_node = canvas_list;
	while (current_node)
	{
		current_canvas = (t_canvas *)current_node->content;
		if (current_canvas && current_canvas->type == type) {
			return (current_canvas);
		}
		current_node = current_node->next;
	}
	printf ("canvas %d not found!\n", type);
	return (NULL);
}


/*
** 
** This function is designed to adjust the height of a canvas to ensure its 
	total byte size is aligned with AVX (Advanced Vector Extensions) 
	requirements. It takes the canvas width and a preferred height as input.
** The function calculates the total byte size of the canvas based on its width,
	 height, and the size of a pixel (t_color). If this total size is not a 
	 multiple of the AVX byte size (32 bytes in this case), the function 
	 computes the additional number of rows needed to align the total size with 
	 the AVX byte size.
** The function returns the adjusted height which, when used, ensures that the 
	total byte size of the canvas is a multiple of the AVX byte size. 
	This alignment can be crucial for performance optimization in certain 
	operations, particularly those involving AVX instructions.
*/
static int	adjusted_height(int width, int preferredHeight)
{
	const int	avx_bytes = 32;
	const int	pixel_bytes = sizeof(t_color);
	const int	total_bytes = width * preferredHeight * pixel_bytes;
	const int	remainder = total_bytes % avx_bytes;

	if (remainder != 0)
	{
		int bytes_needed = avx_bytes - remainder;
		int rows_needed = (bytes_needed + pixel_bytes - 1) / pixel_bytes;
		return (preferredHeight + rows_needed);
	}
	return (preferredHeight);
}



/*
** This function is responsible for setting the boundaries of a canvas within 
	a given space. It takes a pointer to a t_canvas_init_entry structure 
	(representing a canvas), a pointer to the current position (t_point2i),
	a pointer to the current row height (int), and the maximum allowed width
	(int) as inputs.
** The function first adjusts the height of the canvas using adjusted_height to
	ensure AVX alignment. If the canvas is marked to stack (i.e., to be placed
	next to each other horizontally until the max width is reached), it checks
	if the current position plus the canvas width exceeds the max width. If so,
	it moves the canvas to the next row. It then sets the top and bottom bounds
	of the canvas based on the current position and updates the current position
	and row height accordingly.
** For canvases not marked to stack, it simply updates the bounds without
	modifying the current position and row height.
** This function is crucial in dynamically arranging multiple canvas elements
	within a constrained space, respecting their individual sizes and the
	overall layout constraints.
*/

void set_canvas_bounds(t_canvas_init_entry *entry,
	t_point2i *currentPos,
	int *currentRowHeight,
	int maxWidth)
{
	entry->size.y = adjusted_height(entry->size.x, entry->size.y);
	if (entry->stack)
	{
		if (currentPos->x + entry->size.x > maxWidth)
		{
			currentPos->x = 0;
			currentPos->y += *currentRowHeight;
			*currentRowHeight = 0;
		}
		entry->bounds.top = *currentPos;
		entry->bounds.bottom.x = currentPos->x + entry->size.x;
		entry->bounds.bottom.y = currentPos->y + entry->size.y;
		currentPos->x += entry->size.x;
		*currentRowHeight = fmax(*currentRowHeight, entry->size.y);
	}
	else
	{
		entry->bounds.top = entry->position;
		entry->bounds.bottom.x = entry->position.x + entry->size.x;
		entry->bounds.bottom.y = entry->position.y + entry->size.y;
		entry->position.y += entry->size.y;
	}
}
