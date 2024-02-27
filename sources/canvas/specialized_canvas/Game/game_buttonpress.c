/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_buttonpress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2024/02/27 00:49:46 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "draw_utils.h"
#include "game_loop.h"

int	menu_to_game_handle_boutonpress(
	int buttonsym,
	t_point2i mouse_pos,
	void *self,
	t_cub *data)
{
	(void)mouse_pos;
	(void)self;
	if (buttonsym == 1)
	{
		data->game_state = GAMEPLAY;
		data->update = UPDATE;
		printf(("old canvas_list head: %p\n"), data->canvas_list);
		free_canvas_list(data->canvas_list);
		data->canvas_list = initialize_canvas_list(data->game_state,
				((t_setup_by_game_state *)data->setup_canvas));
		printf("new canvas_list head: %p\n", data->canvas_list);
		data->active_canvas = get_canvas_from_list(data->canvas_list, GAME);
		printf("new active canvas: %p\n", data->active_canvas);
		game_init(data, get_canvas_from_list(data->canvas_list, GAME));
	}
	return (0);
}
