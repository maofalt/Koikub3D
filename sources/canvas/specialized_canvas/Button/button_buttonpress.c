/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2023/10/16 21:35:09 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "draw_utils.h"


int	menu_to_edit_map_handle_boutonpress(
	int buttonsym,
	t_point2i mouse_pos,
	void *self,
	t_cub *data)
{
	(void)mouse_pos;
	(void)self;
	if (buttonsym == 1)
	{
		data->game_state = MAP_EDITOR;
		data->update = UPDATE;
		//printf("old active canvas: %p\n", data->active_canvas);
		//printf(("old canvas_list head: %p\n"), data->canvas_list);
		free_canvas_list(data->canvas_list);
		data->canvas_list = initialize_canvas_list(data->game_state,
			((t_setup_by_game_state *)data->setup_canvas));
		//printf("new canvas_list head: %p\n", data->canvas_list);
		data->active_canvas = get_canvas_from_list(data->canvas_list, MAP);
		//printf("new active canvas: %p\n", data->active_canvas);
	}
	return (0);
}
