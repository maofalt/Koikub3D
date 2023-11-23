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

t_canvas_type	detect_clicked_canvas(t_cub *data, t_point2i click_position)
{
	t_canvas		*canvas;
	t_canvas_type	type;
	int				z_index;
	t_list			*canvas_list;

	z_index = -1;
	type = END_MARKER;
	canvas_list = data->canvas_list;
	if (!canvas_list)
		return (type);
	while (canvas_list)
	{
		canvas = (t_canvas *)canvas_list->content;
		if (click_position.x >= canvas->info.bounds.top.x
			&& click_position.x <= canvas->info.bounds.bottom.x
			&& click_position.y >= canvas->info.bounds.top.y
			&& click_position.y <= canvas->info.bounds.bottom.y
			&& canvas->info.z_index > z_index)
		{
			type = canvas->type;
			z_index = canvas->info.z_index;
		}
		canvas_list = canvas_list->next;
	}
	return (type);
}
