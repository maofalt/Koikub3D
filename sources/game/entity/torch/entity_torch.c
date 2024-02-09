/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_torch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:03:25 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/09 03:37:55 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include "game_loop.h"
#include "render_3D.h"
#include "structures.h"

void	entity_torch_update(t_entity *self, t_game_data *game_data)
{
	t_entity_torch_data	*data;
	t_3d_render			*render;
	t_light				*light;

	data = self->data;
	render = &game_data->game_view_render;
	data->pos.x = (render->camera->pos.x - render->camera->dir.y * 0.15) * 0.9
		+ data->pos.x * 0.1;
	data->pos.y = (render->camera->pos.y + render->camera->dir.x * 0.15) * 0.9
		+ data->pos.y * 0.1;
	data->pos.z = (render->camera->pos.z + 0.1) * 0.5 + data->pos.z * 0.5;
	data->dir.x = -(render->camera->dir.x) * 0.2 + data->dir.x * 0.8;
	data->dir.y = -(render->camera->dir.y) * 0.2 + data->dir.y * 0.8;
	light = sparse_array_get(render->lights_data.lights,
			data->light_id);
	light->pos = data->pos;
	light->dir = data->dir;
}

void	entity_torch_draw(t_entity *self, t_game_data *game_data)
{
	(void)self;
	(void)game_data;
}

void	entity_torch_destroy(t_entity *self, t_game_data *game_data)
{
	const t_entity_torch_data	*data = self->data;

	if (self->data)
	{
		if (data->light_id != -1)
			light_destroy(&game_data->game_view_render, data->light_id);
	}
	free(self->data);
}

static int	_init_torch_data(t_game_data *game_data,
		t_entity_torch_data *self_data, t_spawn spawn)
{
	t_light	*light;

	self_data->pos = spawn.pos;
	self_data->dir = spawn.dir;
	self_data->light_id = light_spawn_default(&game_data->game_view_render);
	if (self_data->light_id == -1)
		return (1);
	light = sparse_array_get(game_data->game_view_render.lights_data.lights,
			self_data->light_id);
	light->type = DIRECTIONAL_LIGHT;
	light->pos = self_data->pos;
	light->color = (t_color){.r = 2, .g = 2, .b = 1};
	light->dir = self_data->dir;
	light->intensity = 0.50;
	light->show_lens_flare = false;
	light->use_raycasting = true;
	return (0);
}

t_entity	*entity_torch_spawn(t_game_data *game_data, t_spawn spawn)
{
	t_entity	*self;

	self = entity_default_spawn(game_data);
	if (self == NULL)
		return (NULL);
	self->type = ENTITY_TORCH;
	self->destroy = entity_torch_destroy;
	self->update = entity_torch_update;
	self->data = ft_calloc(1, sizeof(t_entity_torch_data));
	if (self->data == NULL)
	{
		entity_torch_destroy(self, game_data);
		return (NULL);
	}
	if (_init_torch_data(game_data, self->data, spawn))
	{
		entity_torch_destroy(self, game_data);
		return (NULL);
	}
	return (self);
}
