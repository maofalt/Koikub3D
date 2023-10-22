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

// Helper function to initialize a canvas
t_canvas	*initialize_single_canvas(t_point2i size, t_canvas_type type)
{
	t_canvas	*canvas;
	t_color		default_color;
	int			total_pixels;

	canvas = (t_canvas *)aligned_calloc(1, sizeof(t_canvas), 32);
	if (!canvas)
		return (NULL);
	canvas->size = (t_point2i){{size.x, size.y}};
	canvas->scale.x = FINAL_CANVAS_SIZE_X / (double)size.x;
	canvas->scale.y = FINAL_CANVAS_SIZE_Y / (double)size.y;
	canvas->inv_scale.vec = 1.0 / canvas->scale.vec;
	total_pixels = canvas->size.x * canvas->size.y;
	canvas->pixels = (t_color *)aligned_malloc(total_pixels
			* sizeof(t_color), 32);
	if (!canvas->pixels)
		return (free(canvas), NULL);
	ft_memset(&default_color, 0, sizeof(t_color));
	ft_memset(canvas->pixels, 0, total_pixels * sizeof(t_color));
	canvas->transformation_matrix = identity_matrix();
	canvas->dirty_rect_count = 0;
	canvas->matrix_operations = NULL;
	canvas->segments = NULL;
	canvas->type = type;
	return (canvas);
}

void	free_canvas(t_canvas *canvas)
{
	if (!canvas)
		return ;
	if (canvas->pixels)
		free(canvas->pixels);
	if (canvas->matrix_operations)
		ft_lstclear(&canvas->matrix_operations, free);
	if (canvas->segments)
		free(canvas->segments);
	free(canvas);
}
