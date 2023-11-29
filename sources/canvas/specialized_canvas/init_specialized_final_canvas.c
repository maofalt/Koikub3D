/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/16 17:43:36 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

static void    fill_canvas(
            t_canvas *canvas,
            t_color color
            )
{
    t_color                *px;
    unsigned long long    image_size;

    if (color.d == 0)
    {
        ft_memset(canvas->pixels, 0,
            canvas->size.x * canvas->size.y * sizeof(t_color));
        return ;
    }
    px = canvas->pixels;
    image_size = canvas->size.y * canvas->size.x;
    while (image_size > 0)
    {
        *px = color;
        px ++;
        image_size --;
    }
}

t_canvas	*initialize_fin_temp_canvas(t_canvas_init_entry *entry)
{
	t_canvas	*canvas;

	canvas = common_canvas_initialization(entry);
	fill_canvas(canvas, (t_color){.d = (size_t)canvas});
	return (canvas);
}

t_canvas	*initialize_final_canvas(t_canvas_init_entry *entry)
{
	t_canvas	*canvas;

	canvas = common_canvas_initialization(entry);
	fill_canvas(canvas, (t_color){.d = (size_t)canvas});
	return (canvas);
}
