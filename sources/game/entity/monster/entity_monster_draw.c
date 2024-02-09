/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_monster_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 03:05:39 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/09 09:11:19 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "dynamic_array.h"
#include "game_loop.h"
#include "maths_utils.h"
#include "matrix.h"
#include "settings.h"
#include "structures.h"


void	draw_billboard_placeholder(t_3d_render *render, t_billboard *billboard);


void	entity_monster_draw(t_entity *self, t_game_data *game_data)
{
	t_entity_monster_data	*data;
	t_billboard				billboard;

	data = self->data;
	billboard.pos = data->pos;
	billboard.dir = data->dir;
	billboard.right = data->right;
	billboard.size = (t_vector4d){{2, 2, 0, 0}};

	if (data->velocity.x <= 0.005 && data->velocity.y <= 0.005
		&& data->velocity.x >= -0.005 && data->velocity.y >= -0.005
		&& data->acceleration.x == 0 && data->acceleration.y == 0)
		billboard.texture.texture
			= &game_data->map_data.texture_manager->textures[5];
	else
		billboard.texture.texture
			= &game_data->map_data.texture_manager->textures[4];
	billboard.texture.offset = 0;
	draw_billboard_placeholder(&game_data->game_view_render, &billboard);
}
