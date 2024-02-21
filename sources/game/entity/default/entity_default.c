/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:03:25 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 22:49:44 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "dynamic_array.h"

void	entity_default_update(t_entity *self, t_game_data *game_data)
{
	(void)self;
	(void)game_data;
}

void	entity_default_draw(t_entity *self, t_game_data *game_data)
{
	(void)self;
	(void)game_data;
}

void	entity_default_destroy(t_entity *self, t_game_data *game_data)
{
	(void)self;
	(void)game_data;
	self->should_be_destroyed = true;
}

static const t_entity	g_default_entity = {
	.id = 0,
	.type = ENTITY_DEFAULT,
	.data = NULL,
	.physics = {
	.acceleration = {{0, 0, 0}},
	.velocity = {{0, 0, 0}},
	.pos = {{0, 0, 0}},
	.dir = {{0, 0, 0}},
	.friction = 0.0,
	.collision_model = {
	.type = COLLISION_MODEL_NONE}
},
	.update = entity_default_update,
	.draw = entity_default_draw,
	.destroy = entity_default_destroy,
	.should_be_destroyed = false
};

t_entity	*entity_default_spawn(t_game_data *game_data)
{
	int			self_id;
	t_entity	*self;

	self_id = sparse_array_add(game_data->state.entities, &g_default_entity);
	if (self_id == -1)
		return (NULL);
	self = sparse_array_get(game_data->state.entities, self_id);
	self->id = self_id;
	return (self);
}
