

#include "dynamic_array.h"
#include "game_loop.h"
#include "render_3D.h"
#include "structures.h"
#include "maths_utils.h"

void	entity_light_source_draw(t_entity *self, t_game_data *game_data)
{
	(void)self;
	(void)game_data;
}

void	entity_light_source_destroy(t_entity *self, t_game_data *game_data)
{
	const t_entity_light_source_data	*data = self->data;

	if (self->data)
	{
		if (data->light_id != -1)
			light_destroy(&game_data->game_view_render, data->light_id);
	}
	free(self->data);
}

/*
	self_data->light_intensity = 0.5;
	self_data->flicker_duration = 10;
	self_data->flicker_duration_variance = 0.1;
	self_data->flicker_interval = 1000;
	self_data->flicker_interval_variance = 0.2;
	self_data->flicker_intensity_variance = 0.5;*/
static int	_init_light_source_data(
		t_game_data *game_data,
		t_entity *self,
		t_entity_light_source_data *self_data,
		t_spawn spawn)
{
	t_light	*light;

	self_data->light_intensity = 1;
	self_data->flicker_duration = 10;
	self_data->flicker_duration_variance = 0.1;
	self_data->flicker_interval = 15;
	self_data->flicker_interval_variance = 1;
	self_data->flicker_intensity_variance = 2;
	self_data->current_interval_duration = self_data->flicker_interval;
	self->physics.pos = spawn.pos;
	self->physics.dir = spawn.dir;
	self_data->light_id = light_spawn_default(&game_data->game_view_render);
	if (self_data->light_id == -1)
		return (1);
	light = sparse_array_get(game_data->game_view_render.lights_data.lights,
			self_data->light_id);
	light->type = DIRECTIONAL_LIGHT;
	light->pos = self->physics.pos;
	light->color = (t_color){.r = 0, .g = 2, .b = 0};
	light->dir = self->physics.dir;
	light->intensity = self_data->light_intensity;
	light->show_lens_flare = true;
	light->use_raycasting = false;
	return (0);
}

t_entity	*entity_light_source_spawn(t_game_data *game_data, t_spawn spawn)
{
	t_entity	*self;

	self = entity_default_spawn(game_data);
	if (self == NULL)
		return (NULL);
	self->type = ENTITY_LIGHT_SOURCE;
	self->destroy = entity_light_source_destroy;
	self->update = entity_light_source_update;
	self->data = ft_calloc(1, sizeof(t_entity_light_source_data));
	if (self->data == NULL)
	{
		return (NULL);
	}
	if (_init_light_source_data(game_data, self, self->data, spawn))
	{
		return (NULL);
	}
	return (self);
}
