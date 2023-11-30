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

t_canvas_init_func	g_canvas_init_functions[END_MARKER]
	= {
[MAP] = initialize_map_editor_canvas,
[UI] = initialize_ui_canvas,
[BUTTON] = initialize_button_canvas,
[GAME] = initialize_game_canvas,
[FIN_TEMP] = initialize_fin_temp_canvas,
[FINAL] = initialize_final_canvas
};

t_canvas	*initialize_canvas(t_canvas_init_entry *entry)
{
	if (entry->type >= END_MARKER || !g_canvas_init_functions[entry->type])
		return (NULL);
	return (g_canvas_init_functions[entry->type](entry));
}

t_canvas	*common_canvas_initialization(t_canvas_init_entry *entry)
{
	t_canvas	*canvas;
	int			total_pixels;

	canvas = (t_canvas *)aligned_calloc(1, sizeof(t_canvas), 32);
	if (!canvas)
		return (NULL);
	canvas->type = entry->type;
	canvas->size = entry->size;
	canvas->scale.x = FIN_CANVAS_SIZE_X / entry->size.x;
	canvas->scale.y = FIN_CANVAS_SIZE_Y / entry->size.y;
	canvas->inv_scale.vec = 1.0 / canvas->scale.vec;
	canvas->bounds = entry->bounds;
	canvas->z_index = entry->z_index;
	canvas->event_handlers = entry->event_handlers;
	total_pixels = canvas->size.x * canvas->size.y;
	canvas->transparency_key = (t_color){{0, 0, 255, 0}};
	canvas->pixels = (t_color *)aligned_malloc(total_pixels
			* sizeof(t_color), 32);
	if (!canvas->pixels)
		return (free(canvas), NULL);
	ft_memset(canvas->pixels, 0, total_pixels * sizeof(t_color));
	return (canvas);
}
