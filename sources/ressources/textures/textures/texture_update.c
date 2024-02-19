/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:23:11 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/19 22:24:40 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "maths_utils.h"
#include "structures.h"
#include <assert.h>

void	texture_update(t_texture *texture, size_t dt)
{
	texture->current_time += dt;
	if (texture->current_time >= texture->ms_per_frame)
	{
		texture->current_frame = (texture->current_frame + 1)
			% texture->frame_count;
		texture->current_time = texture->current_time % texture->ms_per_frame;
	}
}
