/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 14:19:58 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/28 14:20:04 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "structures_utils.h"

static void	destroy_buffers(t_3d_render *render)
{
	free(render->top_array);
	free(render->bottom_array);
	free(render->buffers.depth);
	free(render->buffers.color);
	free(render->buffers.normal);
	free(render->buffers.world_pos);
	render->top_array = NULL;
	render->bottom_array = NULL;
	render->buffers.depth = NULL;
	render->buffers.color = NULL;
	render->buffers.normal = NULL;
	render->buffers.world_pos = NULL;
}

void	render_3d_destroy(t_3d_render *render)
{
	destroy_buffers(render);
	circular_queue_destroy(render->queue);
	render->queue = NULL;
}
