/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_buttonpress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2024/02/27 00:25:05 by olimarti         ###   ########.fr       */
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
		free_canvas_list(data->canvas_list);
		data->canvas_list = initialize_canvas_list(data->game_state,
				((t_setup_by_game_state *)data->setup_canvas));
		data->active_canvas = get_canvas_from_list(data->canvas_list, MAP);
	}
	return (0);
}
