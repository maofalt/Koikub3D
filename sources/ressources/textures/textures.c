/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:53:13 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/05 00:53:06 by olimarti         ###   ########.fr       */
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

t_img_data	*texture_get_frame_offset(t_texture *texture, int offset)
{
	return (texture->frames[(texture->current_frame + offset)
			% texture->frame_count]);
}

t_img_data	*texture_get_frame(t_texture *texture)
{
	return (texture->frames[texture->current_frame]);
}

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

void	texture_destroy(t_texture *texture)
{
	if (texture)
		free(texture->frames);
}

void	texture_set(t_texture *texture, int frame, t_img_data *img)
{
	assert(frame < texture->frame_count);
	texture->frames[frame] = img;
}
