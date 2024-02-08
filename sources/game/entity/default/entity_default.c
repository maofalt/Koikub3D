/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:03:25 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 22:46:47 by olimarti         ###   ########.fr       */
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

t_entity	*entity_default_spawn(t_game_data *game_data)
{
	t_entity	*self;

	self = dynamic_array_new_element(game_data->state.entities);
	if (self == NULL)
		return (NULL);
	self->id = game_data->state.entities->size - 1;
	self->type = ENTITY_DEFAULT;
	self->data = NULL;
	self->destroy = entity_default_destroy;
	self->update = entity_default_update;
	self->draw = entity_default_draw;
	self->should_be_destroyed = false;

	return (self);
}
