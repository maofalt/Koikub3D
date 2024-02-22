/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_penguin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:03:25 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/21 02:38:53 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include "game_loop.h"
#include "structures.h"

void	entity_penguin_update(t_entity *self, t_game_data *game_data)
{
	(void)self;
	(void)game_data;
	entity_penguin_update_movements(self, game_data);
}

void	entity_penguin_destroy(t_entity *self, t_game_data *game_data)
{
	(void)game_data;
	free(self->data);
}

static void	_init_penguin_data(
	t_entity *self,
	t_spawn spawn)
{
	self->physics.pos = spawn.pos;
	self->physics.dir = spawn.dir;
	self->physics.velocity = (t_vector4d){{0, 0, 0, 0}};
	self->physics.acceleration = (t_vector4d){{0, 0, 0, 0}};
	self->physics.right = (t_vector4d){{spawn.dir.y, -spawn.dir.x, 0, 0}};
	self->physics.friction = DEFAULT_PLAYER_DECELERATION;
	self->physics.collision_model.type = COLLISION_MODEL_DYNAMIC_CYLINDER;
	self->physics.collision_model.dynamic_cylinder.height
		= DEFAULT_PLAYER_HEIGHT;
	self->physics.collision_model.dynamic_cylinder.radius
		= DEFAULT_PLAYER_RADIUS;
}

void	entity_penguin_draw(t_entity *self, t_game_data *game_data);

t_entity	*entity_penguin_spawn(t_game_data *game_data, t_spawn	spawn)
{
	t_entity	*self;

	self = entity_default_spawn(game_data);
	if (self == NULL)
		return (NULL);
	self->type = ENTITY_PENGUIN;
	self->destroy = entity_penguin_destroy;
	self->update = entity_penguin_update;
	self->draw = entity_penguin_draw;
	self->data = ft_calloc(1, sizeof(t_entity_penguin_data));
	if (self->data == NULL)
	{
		return (NULL);
	}
	_init_penguin_data(self, spawn);
	return (self);
}
