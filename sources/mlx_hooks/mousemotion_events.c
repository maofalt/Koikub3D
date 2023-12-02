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


int	ft_handle_mousemotion(int x, int y, t_cub *data)
{
	data->mouse_pos = (t_point2i){{x, y}};
	if (data->drawing == DRAWING && data->update & LINE_REDRAW)
	{	
		data->update |= LINE_REDRAW;
	}
	return (0);
}