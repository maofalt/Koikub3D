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



t_canvas	*initialize_map_editor_canvas(t_canvas_init_entry *entry)
{
	t_canvas	*canvas;

	canvas = common_canvas_initialization(entry);
	canvas->type = MAP;
	canvas->transformation_matrix = identity_matrix();
	canvas->data.map_editor.matrix_operations = NULL;
	canvas->data.map_editor.segments = NULL;
	return (canvas);
}

t_canvas	*initialize_button_canvas(t_canvas_init_entry *entry)
{
	t_canvas	*canvas;

	canvas = common_canvas_initialization(entry).
	return (canvas);
}

