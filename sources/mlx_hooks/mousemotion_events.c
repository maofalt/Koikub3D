/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousemotion_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2024/02/04 22:16:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "mlx_engine.h"

int	ft_handle_mousemotion(int x, int y, t_cub *data)
{
	data->mouse_pos = (t_point2i){{x, y}};
	if (data->drawing == DRAWING && data->update & LINE_REDRAW)
	{
		data->update |= LINE_REDRAW;
	}
	return (0);
}
