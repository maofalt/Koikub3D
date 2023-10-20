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

int	ft_destroy_window(t_cub *data)
{	
	free_everything(*data);
	exit(1);
	return (0);
}

int	ft_handle_keyrelease(int keysym, t_cub *data)
{
	(void)data;
	if (keysym == XK_Escape)
		ft_printf("Escape released\n");
	return (0);
}

int	ft_handle_keypress(int keysym, t_cub *data)
{
	ft_destroy_window_button(keysym, data);
	if (keysym == W_KEY || keysym == S_KEY || keysym == D_KEY
		|| keysym == A_KEY || keysym == LEFT_KEY || keysym == RIGHT_KEY)
		ft_movements_keys(keysym, data);
	data->update = 1;
	return (0);
}

int	ft_handle_boutonpress(int buttonsym, int x, int y, t_cub *data)
{
	t_canvas		*map_canvas;
	const t_color	white_color = (t_color){{255, 255, 255, 255}};

	map_canvas = get_canvas_from_list(data->canvas_list, MAP);
	if (buttonsym == 1)
	{
		data->is_drawing = 1;
		start_drawing(map_canvas, (t_point2d){{x, y}});
		copy_canvas_to_temp(data->canvas_list);
		data->update = 1;
	}
	if (buttonsym == 3)
	{
		data->is_drawing = 0;
		end_drawing(map_canvas, (t_point2d){{x, y}}, white_color);
		data->update = 1;
	}
	return (0);
}

int	ft_handle_mousemotion(int x, int y, t_cub *data)
{
	t_canvas		*map_canvas;
	const t_color	white_color = (t_color){{255, 255, 255, 255}};

	map_canvas = get_canvas_from_list(data->canvas_list, MAP);
	if (data->is_drawing && !data->update)
	{
		copy_temp_to_canvas(data->canvas_list);
		update_drawing(map_canvas, (t_point2d){{x, y}}, white_color);
		data->update = 1;
	}
	return (0);
}
