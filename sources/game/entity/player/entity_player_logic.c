/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_player_logic.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:19:23 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/21 02:46:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include "game_loop.h"
#include "maths_utils.h"
#include "matrix.h"
#include "settings.h"
#include "structures.h"

static void	normalize_vector_3d(t_vector4d *vec)
{
	double	reverse_lenght;
	double	lenght;

	lenght = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (lenght == 0)
		return ;
	reverse_lenght = 1 / lenght;
	vec->vec[0] *= reverse_lenght;
	vec->vec[1] *= reverse_lenght;
	vec->vec[2] *= reverse_lenght;
}

t_vector4d	_get_player_space_acceleration(t_game_data *game_data)
{
	t_vector4d	acceleration;

	acceleration.x = game_data->inputs->action_states[a_move_right]
		- game_data->inputs->action_states[a_move_left];
	acceleration.y = game_data->inputs->action_states[a_move_forward]
		- game_data->inputs->action_states[a_move_backward];
	acceleration.z = game_data->inputs->action_states[a_move_down]
		- game_data->inputs->action_states[a_move_up];
	normalize_vector_3d(&acceleration);
	acceleration.vec *= DEFAULT_PLAYER_ACCELERATION;
	return (acceleration);
}

t_vector4d	_get_player_world_acceleration(
	t_entity *self,
	t_game_data *game_data)
{
	t_vector4d	acceleration;
	t_vector4d	world_space_acceleration;

	acceleration = _get_player_space_acceleration(game_data);
	world_space_acceleration.x = acceleration.x * self->physics.right.x
		+ acceleration.y * self->physics.dir.x;
	world_space_acceleration.y = acceleration.x * self->physics.right.y
		+ acceleration.y * self->physics.dir.y;
	world_space_acceleration.z = acceleration.z;
	return (world_space_acceleration);
}

void	_update_player_direction(
		t_entity *self,
		t_game_data *game_data)
{
	const double	angle_scale = DEFAULT_PLAYER_ROTATION_SPEED;
	double			angle_movement;
	t_matrix3x3		transformation;
	t_point2d		rotated_dir;

	angle_movement = angle_scale
		* (game_data->inputs->action_states[a_turn_right]
			- game_data->inputs->action_states[a_turn_left]);
	transformation = rotation_matrix(angle_movement);
	rotated_dir = matrix_vector_multiply(transformation,
			vector4d_to_point2d(&self->physics.dir));
	self->physics.dir = point2d_to_vector4d(&rotated_dir);
	self->physics.right = self->physics.dir;
	self->physics.right.x = -self->physics.dir.y;
	self->physics.right.y = self->physics.dir.x;
}

void	entity_player_update_movements(t_entity *self, t_game_data *game_data)
{
	t_entity_player_data	*data;
	t_vector4d				world_space_acceleration;

	data = self->data;
	world_space_acceleration
		= _get_player_world_acceleration(self, game_data);
	self->physics.acceleration = world_space_acceleration;
	_update_player_direction(self, game_data);
}
