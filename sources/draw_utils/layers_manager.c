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

static int	adjusted_height(int desired_height)
{
	static const int	single_row_bytes = FINAL_CANVAS_SIZE_X
		* sizeof(t_color);

	return (((desired_height * single_row_bytes + 31)
			/ 32) * 32 / single_row_bytes);
}

const t_canvas_init_entry	*get_canvas_init_table(void)
{
	const int					map_height = adjusted_height(1072);
	const int					ui_height = adjusted_height(1000);
	const int					final_height = adjusted_height(1072);
	const int					final_temp_height = adjusted_height(1072);
	static t_canvas_init_entry	canvas_init_table[] = {
		{.size = {MAP_CANVAS_SIZE_X, 0},
		 .type = MAP, .z_index = MAP_Z_INDEX, .position = {0, 0}},
		{.size = {UI_CANVAS_SIZE_X, 0},
		 .type = UI, .z_index = UI_Z_INDEX, .position = {0, 0}},
		{.size = {FINAL_CANVAS_SIZE_X, 0},
		 .type = FINAL, .z_index = FINAL_Z_INDEX, .position = {0, 0}},
		{.size = {MAP_CANVAS_SIZE_X, 0},
		 .type = FINAL_TEMP, .z_index = FINAL_TEMP_Z_INDEX,
		 .position = {0, 0}},
		{.size = {0, 0}, .type = END_MARKER, .z_index = 0, .position = {0, 0}}
	};

	canvas_init_table[0].size.y = map_height;
	canvas_init_table[1].size.y = ui_height;
	canvas_init_table[2].size.y = final_height;
	canvas_init_table[3].size.y = final_temp_height;

	return (canvas_init_table);
}

