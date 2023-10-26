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
	new_node->next = *canvas_list;
	*canvas_list = new_node;
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

t_list	*initialize_canvas_list(void)
{
	const t_canvas_init_entry	*canvas_init_table = get_canvas_init_table();
	t_list						*canvas_list;
	t_list						*new_node;
	size_t						i;

	canvas_list = NULL;
	i = 0;
	while (canvas_init_table[i].type != END_MARKER)
	{
		new_node = initialize_canvas_and_add_to_list(canvas_init_table[i].size,
				canvas_init_table[i].type,
				&canvas_list);
		if (!new_node)
			return (free_canvas_list(canvas_list), NULL);
		i++;
	}
	return (canvas_list);
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
		if (current_canvas && current_canvas->type == type)
			return (current_canvas);
		current_node = current_node->next;
	}
	return (NULL);
}

static int adjusted_height(int width, int preferredHeight) {
    const int avx_bytes = 32;
    const int pixel_bytes = sizeof(t_color);
    int total_bytes = width * preferredHeight * pixel_bytes;
    int remainder = total_bytes % avx_bytes;

    // If the total byte size isn't aligned with AVX, calculate how many more rows are needed
    if (remainder != 0) {
        int bytes_needed = avx_bytes - remainder;
        int rows_needed = (bytes_needed + pixel_bytes - 1) / pixel_bytes;  // this ensures we round up
        return preferredHeight + rows_needed;
    }

    // If the preferred height already meets the alignment, just return that
    return preferredHeight;
}



const t_canvas_init_entry	*get_canvas_init_table(void)
{
	static t_canvas_init_entry	canvas_init_table[] = {
	{.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}}, .type = MAP,
		.z_index = MAP_Z_INDEX, .position = (t_point2i){{0, 0}}, .stack = true},
	{.size = (t_point2i){{UI_CANVAS_SIZE_X, UI_CANVAS_SIZE_Y}}, .type = UI,
		.z_index = UI_Z_INDEX, .position = (t_point2i){{0, 0}}, .stack = true},
	{.size = (t_point2i){{FINAL_CANVAS_SIZE_X, FINAL_CANVAS_SIZE_Y}}, .type = FINAL,
		.z_index = FINAL_Z_INDEX, .position = (t_point2i){{0, 0}}},
	{.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
		.type = FINAL_TEMP, .z_index = FINAL_TEMP_Z_INDEX,
		.position = (t_point2i){{0, 0}}},
	{.type = END_MARKER, .z_index = 0}
	};
	t_point2i					current_pos;
	int							current_row_height;
	int							i;

	current_pos = (t_point2i){{0, 0}};
	current_row_height = 0;
	i = 0;
	while (canvas_init_table[i].type != END_MARKER)
	{
		set_canvas_bounds(&canvas_init_table[i], &current_pos,
			&current_row_height, 1920);
		i++;
	}
	return (canvas_init_table);
}

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
		entry->bounds.top = *currentPos;
		entry->bounds.bottom.x = currentPos->x + entry->size.x;
		entry->bounds.bottom.y = currentPos->y + entry->size.y;
		currentPos->y += entry->size.y;
	}
}
