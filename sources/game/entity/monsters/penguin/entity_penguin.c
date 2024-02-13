/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_penguin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:03:25 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/13 21:21:47 by olimarti         ###   ########.fr       */
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

static void	_init_penguin_data(t_entity_penguin_data *self_data,
		t_spawn spawn)
{
	self_data->pos = spawn.pos;
	self_data->dir = spawn.dir;
	self_data->velocity = (t_vector4d){{0, 0, 0, 0}};
	self_data->acceleration = (t_vector4d){{0, 0, 0, 0}};
	self_data->right = (t_vector4d){{spawn.dir.y, -spawn.dir.x, 0, 0}};
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
	_init_penguin_data(self->data, spawn);
	return (self);
}
