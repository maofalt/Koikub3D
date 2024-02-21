/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:09:33 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/21 02:50:57 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_loop.h"

void	entities_update(t_game_data *game_data)
{
	t_entity *const	entities = game_data->state.entities->buffer;
	int				i;

	i = 0;
	while (i < game_data->state.entities->size)
	{
		entities[i].update(&entities[i], game_data);
		apply_physics_entity(&entities[i], game_data, 1);
		i++;
	}
}

void	entities_draw(t_game_data *game_data)
{
	t_entity *const	entities = game_data->state.entities->buffer;
	int				i;

	i = 0;
	while (i < game_data->state.entities->size)
	{
		entities[i].draw(&entities[i], game_data);
		i++;
	}
}

void	entities_destroy_marked(t_game_data *game_data)
{
	t_entity *const	entities = game_data->state.entities->buffer;
	t_entity		*entity;
	int				i;

	i = 0;
	while (i < game_data->state.entities->size)
	{
		entity = &entities[i];
		if (entity->should_be_destroyed)
		{
			entity->destroy(entity, game_data);
			sparse_array_remove(game_data->state.entities, entity->id);
		}
		else
			i++;
	}
}

void	entities_destroy_all(t_game_data *game_data)
{
	t_entity		*entities;
	t_entity		*entity;
	int				i;

	if (game_data->state.entities == NULL)
		return ;
	entities = game_data->state.entities->buffer;
	i = 0;
	while (i < game_data->state.entities->size)
	{
		entity = &entities[i];
		entity->destroy(entity, game_data);
		i++;
	}
	sparse_array_remove_all(game_data->state.entities);
}
