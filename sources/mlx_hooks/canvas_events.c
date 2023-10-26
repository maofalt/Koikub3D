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
	int			i;
	t_canvas	*canvas;

	i = 0;
	while (i < END_MARKER)
	{
		canvas = get_canvas_from_list(data->canvas_list, i);
		if (click_position.x >= canvas->bounds.top.x
			&& click_position.x <= canvas->bounds.bottom.x
			&& click_position.y >= canvas->bounds.top.y
			&& click_position.y <= canvas->bounds.bottom.y)
			return (canvas->type);
		i++;
	}
	return (END_MARKER);
}
