/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 14:18:20 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/08 03:34:42 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "structures.h"
#include "settings.h"

static int	init_buffers(t_3d_render *render, int width, int height)
{
	render->top_array = ft_calloc(render->width, sizeof(double));
	render->bottom_array = ft_calloc(render->width, sizeof(double));
	render->buffers.depth = ft_calloc(width * height,
			sizeof(render->buffers.depth[0]));
	render->buffers.color = ft_calloc(width * height,
			sizeof(render->buffers.color[0]));
	render->buffers.color_bis = ft_calloc(width * height,
			sizeof(render->buffers.color[0]));
	render->buffers.normal = ft_calloc(width * height,
			sizeof(render->buffers.normal[0]));
	render->buffers.world_pos = ft_calloc(width * height,
			sizeof(render->buffers.world_pos[0]));
	if (render->top_array == NULL || render->bottom_array == NULL
		|| render->buffers.depth == NULL || render->buffers.color == NULL
		|| render->buffers.normal == NULL || render->buffers.world_pos == NULL)
	{
		return (1);
	}
	return (0);
}

int	render_3d_init(t_3d_render *render, t_canvas *canvas, t_camera *camera,
		t_map_data *map)
{
	render->canvas = canvas;
	render->camera = camera;
	render->camera->fov = DEFAULT_FOV;
	render->scale_factor_x = 3;
	render->scale_factor_y = 3;
	render->width = canvas->size.x / render->scale_factor_x;
	render->height = canvas->size.y / render->scale_factor_y;
	render->map = map;
	render->middle.x = render->width / 2;
	render->middle.y = render->height / 2;
	render->middle.w = 0;
	render->middle.z = 0;
	render_init_lights(render);
	render->queue = circular_queue_create(RENDER_QUEUE_SIZE,
			sizeof(t_render_item_queue));
	if (render->queue == NULL || init_buffers(render, render->width,
			render->height))
	{
		render_3d_destroy(render);
		return (1);
	}
	return (0);
}
