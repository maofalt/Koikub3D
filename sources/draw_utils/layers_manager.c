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

// Helper function to initialize a canvas
t_canvas	*initialize_single_canvas(t_point2i size, t_canvas_type type)
{
	t_canvas	*canvas;
	t_color		default_color;
	int			total_pixels;

	canvas = (t_canvas *)aligned_calloc(1, sizeof(t_canvas), 32);
	if (!canvas)
		return (NULL);
	canvas->size = (t_point2i){{size.x, size.y}};
	canvas->scale.x = FINAL_CANVAS_SIZE_X / (double)size.x;
	canvas->scale.y = FINAL_CANVAS_SIZE_Y / (double)size.y;
	canvas->inv_scale.vec = 1.0 / canvas->scale.vec;
	total_pixels = canvas->size.x * canvas->size.y;
	canvas->pixels = (t_color *)aligned_malloc(total_pixels
			* sizeof(t_color), 32);
	if (!canvas->pixels)
		return (free(canvas), NULL);
	ft_memset(&default_color, 0, sizeof(t_color));
	ft_memset(canvas->pixels, 0, total_pixels * sizeof(t_color));
	canvas->transformation_matrix = identity_matrix();
	canvas->dirty_rect_count = 0;
	canvas->matrix_operations = NULL;
	canvas->segments = NULL;
	canvas->type = type;
	return (canvas);
}

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

void	free_canvas(t_canvas *canvas)
{
	if (!canvas)
		return ;
	if (canvas->pixels)
		free(canvas->pixels);
	if (canvas->matrix_operations)
		ft_lstclear(&canvas->matrix_operations, free);
	if (canvas->segments)
		free(canvas->segments);
	free(canvas);
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
}

t_list	*initialize_canvas_list(t_point2i size_map,
		t_point2i size_ui,
		t_point2i size_final)
{
	static t_canvas_init_entry	canvas_init_table[]
		= {{{{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}}, MAP},
	{{{UI_CANVAS_SIZE_X, UI_CANVAS_SIZE_Y}}, UI},
	{{{FINAL_CANVAS_SIZE_X, FINAL_CANVAS_SIZE_Y}}, FINAL},
	{{{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}}, FINAL_TEMP}};
	t_list						*canvas_list;
	t_list						*new_node;
	size_t						i;

	canvas_list = NULL;
	canvas_init_table[0].size = size_map;
	canvas_init_table[1].size = size_ui;
	canvas_init_table[2].size = size_final;
	canvas_init_table[3].size = size_final;
	i = 0;
	while (i < sizeof(canvas_init_table) / sizeof(canvas_init_table[0]))
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
