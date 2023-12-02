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

t_canvas_free_func	g_canvas_free_functions[END_MARKER]
	= {
[MAP] = free_map_editor,
[UI] = free_ui,
[BUTTON] = free_button,
[GAME] = free_game,
[FIN_TEMP] = NULL,
[FINAL] = NULL
};

void	free_canvas_by_type(t_canvas *canvas)
{
	if (canvas->type >= END_MARKER || !g_canvas_free_functions[canvas->type])
		return ;
	return (g_canvas_free_functions[canvas->type](canvas));
}

void	free_canvas(t_canvas *canvas)
{
	if (!canvas)
		return ;
	if (canvas->pixels)
		aligned_free(canvas->pixels);
	free_canvas_by_type(canvas);
	aligned_free(canvas);
}
