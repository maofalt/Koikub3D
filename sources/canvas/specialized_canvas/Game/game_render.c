/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2024/02/27 00:26:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "draw_utils.h"
#include "assets.h"

// //Fill canvas with color either fill it with  the texture
// int	button_render(void *self, t_cub *data)
// {
// 	t_canvas		*button;
// 	t_button_data	*button_data;

// 	button = (t_canvas *)self;
// 	button_data = &button->data.button;

// 	if (button_data->img == NULL)
// 	{
// 		button_data->img = get_ui_asset(button_data->asset, data->ui_images);
// 		if (button_data->img == NULL)
// 			return (0);
// 		fill_canvas_with_image(button, button_data->img);
// 	}
// 	return (0);
// }
