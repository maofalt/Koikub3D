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
	printf("menu_to_edit_map_handle_boutonpress\n");
	if (buttonsym == 1)
	{
		printf("trying to change game state\n");
		data->game_state = MAP_EDITOR;
		data->update = UPDATE;
		free_canvas_list(data->canvas_list);
		data->canvas_list = initialize_canvas_list(data->game_state,
			((t_setup_by_game_state *)data->setup_canvas));
	}
	return (0);
}
