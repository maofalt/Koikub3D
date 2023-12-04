/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_buttonpress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2023/12/03 23:24:17 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "draw_utils.h"
#include "game_loop.h"

//TODO: move it
int	map_convert(t_cub *data);

int	game_init(t_cub *data, t_canvas *canvas)
{
	data->update = UPDATE;
	printf("game_init\n");
	if (map_convert(data))
		return (free_everything(*data), 1);
	if (game_render_init(data, canvas))
		return (free_everything(*data), 1);
	return (0);
}

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
