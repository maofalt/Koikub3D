/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_get_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:23:11 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/19 22:25:28 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "maths_utils.h"
#include "structures.h"
#include <assert.h>

t_img_data	*texture_get_frame_offset(t_texture *texture, int offset)
{
	return (texture->frames[(texture->current_frame + offset)
			% texture->frame_count]);
}

t_img_data	*texture_get_frame(t_texture *texture)
{
	return (texture->frames[texture->current_frame]);
}
