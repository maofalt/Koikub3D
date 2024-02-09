/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_player_logic.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:19:23 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/08 16:36:00 by olimarti         ###   ########.fr       */
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

t_vector4d	_get_player_world_acceleration(t_entity_player_data *self_data,
		t_game_data *game_data)
{
	t_vector4d	acceleration;
	t_vector4d	world_space_acceleration;

	acceleration = _get_player_space_acceleration(game_data);
	world_space_acceleration.x = acceleration.x * self_data->right.x
		+ acceleration.y * self_data->dir.x;
	world_space_acceleration.y = acceleration.x * self_data->right.y
		+ acceleration.y * self_data->dir.y;
	world_space_acceleration.z = acceleration.z;
	return (world_space_acceleration);
}

void	_update_player_direction(t_entity_player_data *self_data,
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
			vector4d_to_point2d(&self_data->dir));
	self_data->dir = point2d_to_vector4d(&rotated_dir);
	self_data->right = self_data->dir;
	self_data->right.x = -self_data->dir.y;
	self_data->right.y = self_data->dir.x;
}


static double dot_product_3d(t_vector4d *vec1, t_vector4d *vec2)
{
	double result = vec1->x * vec2->x + vec1->y * vec2->y + +vec1->z * vec2->z;

	return (result);
}

void	apply_collision_correction(t_entity_player_data *data, t_game_data *game_data)
{
	t_vector4d			sliding_vector;
	t_vector4d			new_pos;
	double				dot_product;
	t_collision_info	collision_info;
	int					i;

	i = 5;
	new_pos.vec = data->pos.vec + data->velocity.vec * game_data->delta_time;
	collision_info
		= check_collision_cylinder(new_pos, DEFAULT_PLAYER_RADIUS,
			DEFAULT_PLAYER_HEIGHT, &game_data->game_view_render);
	while (collision_info.collision && --i)
	{
		normalize_vector_3d(&collision_info.collision_normal);
		dot_product = dot_product_3d(&data->velocity,
				&collision_info.collision_normal);
		sliding_vector.vec = data->velocity.vec
			- 1.0 * dot_product * collision_info.collision_normal.vec;
		data->velocity = sliding_vector;
		new_pos.vec = data->pos.vec
			+ data->velocity.vec * game_data->delta_time;
		collision_info
			= check_collision_cylinder(new_pos, DEFAULT_PLAYER_RADIUS,
				DEFAULT_PLAYER_HEIGHT, &game_data->game_view_render);
	}
}

void	entity_player_update_movements(t_entity *self, t_game_data *game_data)
{
	t_entity_player_data	*data;
	t_vector4d				world_space_acceleration;

	data = self->data;
	world_space_acceleration = _get_player_world_acceleration(data, game_data);
	data->velocity.vec += world_space_acceleration.vec * game_data->delta_time;
	data->velocity.vec *= 1 - DEFAULT_PLAYER_DECELERATION
		* game_data->delta_time;
	apply_collision_correction(data, game_data);
	data->pos.vec += data->velocity.vec * game_data->delta_time;
	_update_player_direction(data, game_data);

}
