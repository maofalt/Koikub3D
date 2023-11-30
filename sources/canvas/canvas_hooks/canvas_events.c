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

void	*detect_clicked_canvas(t_cub *data, t_point2i click_position)
{
	t_canvas		*canvas;
	t_canvas		*canvas_to_return;
	int				z_index;
	t_list			*canvas_list;

	z_index = -1;
	canvas_to_return = NULL;
	canvas_list = data->canvas_list;
	if (!canvas_list)
		return (canvas_to_return);
	while (canvas_list)
	{
		canvas = (t_canvas *)canvas_list->content;
		if (click_position.x >= canvas->bounds.top.x
			&& click_position.x <= canvas->bounds.bottom.x
			&& click_position.y >= canvas->bounds.top.y
			&& click_position.y <= canvas->bounds.bottom.y
			&& canvas->z_index > z_index)
		{
			canvas_to_return = canvas;
			z_index = canvas->z_index;
		}
		canvas_list = canvas_list->next;
	}
	return (canvas_to_return);
}
