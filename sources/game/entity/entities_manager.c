/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:09:33 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 19:11:18 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_loop.h"

void	entities_update(t_game_data *game_data)
{
	size_t		i;
	t_entity	*entity;

	i = 0;
	while (i < game_data->state.entities->size)
	{
		entity = dynamic_array_get(game_data->state.entities, i);
		entity->update(entity, game_data);
		i++;
	}
}

void	entities_draw(t_game_data *game_data)
{
	size_t		i;
	t_entity	*entity;

	i = 0;
	while (i < game_data->state.entities->size)
	{
		entity = dynamic_array_get(game_data->state.entities, i);
		entity->draw(entity, game_data);
		i++;
	}
}

void	entities_destroy_marked(t_game_data *game_data)
{
	size_t		i;
	t_entity	*entity;

	i = 0;
	while (i < game_data->state.entities->size)
	{
		entity = dynamic_array_get(game_data->state.entities, i);
		if (entity->should_be_destroyed)
		{
			entity->destroy(entity, game_data);
			dynamic_array_remove(game_data->state.entities, i);
		}
		else
			i++;
	}
}

