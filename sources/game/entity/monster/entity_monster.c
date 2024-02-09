/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_monster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:03:25 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/09 08:59:35 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include "game_loop.h"
#include "structures.h"

void	entity_monster_update(t_entity *self, t_game_data *game_data)
{
	(void)self;
	(void)game_data;
	entity_monster_update_movements(self, game_data);
}

void	entity_monster_destroy(t_entity *self, t_game_data *game_data)
{
	(void)game_data;
	free(self->data);
}

static void	_init_monster_data(t_entity_monster_data *self_data,
		t_spawn spawn)
{
	self_data->pos = spawn.pos;
	self_data->dir = spawn.dir;
	self_data->velocity = (t_vector4d){{0, 0, 0, 0}};
	self_data->acceleration = (t_vector4d){{0, 0, 0, 0}};
	self_data->right = (t_vector4d){{spawn.dir.y, -spawn.dir.x, 0, 0}};
}

void	entity_monster_draw(t_entity *self, t_game_data *game_data);


t_entity	*entity_monster_spawn(t_game_data *game_data, t_spawn	spawn)
{
	t_entity	*self;

	self = entity_default_spawn(game_data);
	if (self == NULL)
		return (NULL);
	self->type = ENTITY_MONSTER;
	self->destroy = entity_monster_destroy;
	self->update = entity_monster_update;
	self->draw = entity_monster_draw;
	self->data = ft_calloc(1, sizeof(t_entity_monster_data));
	if (self->data == NULL)
	{
		entity_monster_destroy(self, game_data);
		return (NULL);
	}
	_init_monster_data(self->data, spawn);
	return (self);
}
