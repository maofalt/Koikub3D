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
	t_canvas_type  type;

	i = 0;
	printf("Detected click on %d %d\n", click_position.x, click_position.y);
	while (i < END_MARKER)
	{
		canvas = get_canvas_from_list(data->canvas_list, i++);
		if (!canvas)
			continue ;
		type = canvas->type;
		printf("\tclicked on canvas %s\n", (type == 0 )? "MAP" : (type == 1 )? "UI" : (type == 2)? "GAME" : (type == 3 )? "FINAL" : (type == 4 )? "FIN_TEMP" : "END_MARKER");
		printf("\t\tcanvas bounds: %d %d %d %d\n", canvas->info.bounds.top.x, canvas->info.bounds.top.y, canvas->info.bounds.bottom.x, canvas->info.bounds.bottom.y);
		if (click_position.x >= canvas->info.bounds.top.x
			&& click_position.x <= canvas->info.bounds.bottom.x
			&& click_position.y >= canvas->info.bounds.top.y
			&& click_position.y <= canvas->info.bounds.bottom.y)
			return (canvas->type);
	}
	return (END_MARKER);
}
