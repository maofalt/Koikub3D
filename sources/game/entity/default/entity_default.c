/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:03:25 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/09 01:17:29 by olimarti         ###   ########.fr       */
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
	int				self_id;
	t_entity		*self;
	const t_entity	default_entity = {
		.id = 0,
		.type = ENTITY_DEFAULT,
		.data = NULL,
		.destroy = entity_default_destroy,
		.update = entity_default_update,
		.draw = entity_default_draw,
		.should_be_destroyed = false
	};

	self_id = sparse_array_add(game_data->state.entities, &default_entity);
	if (self_id == -1)
		return (NULL);
	self = sparse_array_get(game_data->state.entities, self_id);
	self->id = self_id;
	return (self);
}
