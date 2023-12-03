/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2023/12/03 23:10:27 by olimarti         ###   ########.fr       */
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

int	ft_handle_game_keyrelease(int keysym, __attribute_maybe_unused__ void *canvas, t_cub *data)
{
	(void)data;
	if (keysym == XK_Escape)
		ft_printf("Escape released\n");
	ft_movements_keys(keysym, data, 0);
	return (0);
}

int	ft_handle_game_keypress(int keysym, __attribute_maybe_unused__ void *canvas, t_cub *data)
{
	ft_destroy_window_button(keysym, data);
	ft_movements_keys(keysym, data, 1);
	data->update = 1;
	return (0);
}





// int	ft_handle_boutonpress(int buttonsym, int x, int y, t_cub *data)
// {
// 	printf("butoon\n");
// 	// t_canvas	*map_canvas = get_canvas_from_list(data->canvas_list,
// 	// 		MAP);
// 	// const t_color	white_color = (t_color){{255, 255, 255, 255}};

// 	// (void)x;
// 	// (void)y;
// 	// if (buttonsym == 1)
// 	// {
// 	// 	printf("Left button pressed\n");
// 	// 	data->is_drawing = 1;
// 	// 	start_drawing(map_canvas, (t_point2d){{x, y}});
// 	// 	copy_canvas_to_temp(data->canvas_list);
// 	// 	data->update = 1;
// 	// }
// 	// if (buttonsym == 3)
// 	// {
// 	// 	printf("Right button pressed\n");
// 	// 	data->is_drawing = 0;
// 	// 	end_drawing(map_canvas, (t_point2d){{x, y}}, white_color);
// 	// 	data->update = 1;
// 	// }
// 	// return (0);
// }

// int	ft_handle_mousemotion(int x, int y, t_cub *data)
// {
// 	print("butoon\n");
// 	// t_canvas	*map_canvas = get_canvas_from_list(data->canvas_list, MAP);
// 	// const t_color	white_color = (t_color){{255, 255, 255, 255}};

// 	// if (data->is_drawing && !data->update)
// 	// {
// 	// 	copy_temp_to_canvas(data->canvas_list);
// 	// 	update_drawing(map_canvas, (t_point2d){{x, y}}, white_color);
// 	// 	data->update = 1;
// 	// }
// 	// return (0);
// }
