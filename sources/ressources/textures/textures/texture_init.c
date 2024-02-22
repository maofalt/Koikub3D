/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:23:11 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/19 22:23:45 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "maths_utils.h"
#include "structures.h"
#include <assert.h>

int	texture_init(t_texture *texture, int frames_count, int ms_per_frame)
{
	texture->frames = ft_calloc(frames_count, sizeof(texture->frames));
	if (texture->frames == NULL)
		return (1);
	texture->frame_count = frames_count;
	texture->is_animated = (frames_count > 0);
	texture->ms_per_frame = ms_per_frame;
	texture->current_frame = 0;
	return (0);
}
