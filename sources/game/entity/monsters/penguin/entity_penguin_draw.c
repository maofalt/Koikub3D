/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_penguin_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 03:05:39 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/25 01:29:57 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include "game_loop.h"
#include "maths_utils.h"
#include "matrix.h"
#include "settings.h"
#include "structures.h"
#include "render_3D.h"

void	entity_penguin_draw(t_entity *self, t_game_data *game_data)
{
	t_billboard				billboard;

	billboard.pos = self->physics.pos;
	billboard.dir = self->physics.dir;
	billboard.right = self->physics.right;
	billboard.size = (t_vector4d){{2, 2, 0, 0}};
	if (self->physics.velocity.x <= 0.005 && self->physics.velocity.y <= 0.005
		&& self->physics.velocity.x >= -0.005
		&& self->physics.velocity.y >= -0.005
		&& self->physics.acceleration.x == 0
		&& self->physics.acceleration.y == 0)
		billboard.texture.texture
			= &game_data->map_data.texture_manager
			->textures[TEXTURE_PENGUIN_IDLE];
	else
		billboard.texture.texture
			= &game_data->map_data.texture_manager
			->textures[TEXTURE_PENGUIN_WALK];
	billboard.texture.offset = 0;
	draw_billboard(&game_data->game_view_render, &billboard);
}
