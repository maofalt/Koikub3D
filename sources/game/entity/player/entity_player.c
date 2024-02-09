/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:03:25 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 18:52:06 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include "game_loop.h"
#include "structures.h"

void	entity_player_update(t_entity *self, t_game_data *game_data)
{
	entity_player_update_movements(self, game_data);
}

void	entity_player_destroy(t_entity *self, t_game_data *game_data)
{
	(void)game_data;
	free(self->data);
}

static void	_init_player_data(t_entity_player_data *self_data,
		t_spawn spawn)
{
	self_data->pos = spawn.pos;
	self_data->dir = spawn.dir;
	self_data->velocity = (t_vector4d){{0, 0, 0, 0}};
	self_data->right = (t_vector4d){{0, 0, 0, 0}};
}

t_entity	*entity_player_spawn(t_game_data *game_data, t_spawn	spawn)
{
	t_entity	*self;

	self = entity_default_spawn(game_data);
	if (self == NULL)
		return (NULL);
	self->type = ENTITY_PLAYER;
	self->destroy = entity_player_destroy;
	self->update = entity_player_update;
	self->data = ft_calloc(1, sizeof(t_entity_player_data));
	if (self->data == NULL)
	{
		entity_player_destroy(self, game_data);
		return (NULL);
	}
	_init_player_data(self->data, spawn);
	return (self);
}
