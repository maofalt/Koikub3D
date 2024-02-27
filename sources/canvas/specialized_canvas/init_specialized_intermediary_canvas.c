/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_specialized_intermediary_canvas.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 19:22:27 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

t_canvas	*initialize_map_editor_canvas(t_canvas_init_entry *entry)
{
	t_canvas	*canvas;

	canvas = common_canvas_initialization(entry);
	if (!canvas)
		return (NULL);
	canvas->type = MAP;
	canvas->data.map_editor.transformation_matrix = identity_matrix();
	canvas->data.map_editor.matrix_operations = NULL;
	canvas->data.map_editor.segments = NULL;
	fill_canvas(canvas, (t_color){.d = (size_t)canvas});
	return (canvas);
}

t_canvas	*initialize_button_canvas(t_canvas_init_entry *entry)
{
	t_canvas		*canvas;

	canvas = common_canvas_initialization(entry);
	if (!canvas)
		return (NULL);
	canvas->data.button.asset = entry->asset;
	ft_strcpy(canvas->data.button.text, entry->text);
	canvas->data.button.img = NULL;
	canvas->data.button.fit_mode = entry->fit_mode;
	canvas->data.button.action_on_click = NULL;
	fill_canvas(canvas, (t_color){.d = (size_t)canvas});
	return (canvas);
}

t_canvas	*initialize_ui_canvas(t_canvas_init_entry *entry)
{
	t_canvas	*canvas;

	canvas = common_canvas_initialization(entry);
	fill_canvas(canvas, (t_color){.d = (size_t)canvas});
	return (canvas);
}

t_canvas	*initialize_game_canvas(t_canvas_init_entry *entry)
{
	t_canvas	*canvas;

	canvas = common_canvas_initialization(entry);
	fill_canvas(canvas, (t_color){.d = (size_t)canvas});
	return (canvas);
}
